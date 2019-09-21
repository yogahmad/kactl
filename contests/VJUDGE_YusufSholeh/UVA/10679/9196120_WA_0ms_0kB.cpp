#include<bits/stdc++.h>
using namespace std;

const int NALPHABET = 52;
 
struct Node {
  Node** children;	
  Node** go;
  bool leaf;
  char charToParent;
  Node* parent;
  Node* suffLink;
  Node* dictSuffLink;
  int count, value;
 
  Node(){
    children =new Node*[NALPHABET];
    go = new Node*[NALPHABET];
    for(int i =0; i < NALPHABET;++i){
      children[i]= go[i]=NULL;
    }
    parent = suffLink = dictSuffLink =NULL;
    leaf =false;
    count = 0;
  }
};
 
Node* createRoot(){
  Node* node =new Node();
  node->suffLink = node;
  return node;
}
 
void addString(Node* node,const string& s,int value =-1){
  for(int i =0; i < s.length();++i){
    int c = s[i] - 'a';
	
	if (c < 0) {
		c = s[i] - 'A' + 26;
	}
	
    if(node->children[c]==NULL){
      Node* n =new Node();
      n->parent = node;
      n->charToParent = s[i];
      node->children[c]= n;
    }
    node = node->children[c];
  }
  node->leaf =true;
  node->count++;
  node->value = value;
}
 
Node* suffLink(Node* node);
Node* dictSuffLink(Node* node);
Node* go(Node* node,char ch);
int calc(Node* node);
 
Node* suffLink(Node* node){
  if(node->suffLink ==NULL){
    if(node->parent->parent ==NULL){
      node->suffLink = node->parent;
    }else{
      node->suffLink = go(suffLink(node->parent),node->charToParent);
    }
  }
  return node->suffLink;
}
 
Node* dictSuffLink(Node* node){
  if(node->dictSuffLink ==NULL){
    Node* n = suffLink(node);
    if(node == n){
      node->dictSuffLink = node;
    }else{
      while(!n->leaf && n->parent !=NULL){
        n = dictSuffLink(n);
      }
      node->dictSuffLink = n;
    }
  }
  return node->dictSuffLink;
}
 
Node* go(Node* node,char ch){
  int c = ch -'a';
  if(node->go[c]==NULL){
    if(node->children[c]!=NULL){
      node->go[c]= node->children[c];
    }else{
      node->go[c]= node->parent ==NULL? node : go(suffLink(node), ch);
    }
  }
  return node->go[c];
}
 
int calc(Node* node){
  if(node->parent ==NULL){
    return 0;
  }else{
    return node->count + calc(dictSuffLink(node));
  }
}
 
 
#define MAX 300000
int ada[MAX];
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int tc; cin >> tc;
	while(tc--) {
		
		string x; cin >> x;
		memset(ada,0,sizeof(ada));
		Node* root = createRoot();
		int ampas; string d;
		cin >> ampas;
		for(int i = 1; i <= ampas; i++) {
			cin >> d;
			addString(root,d,i-1);
		}
		
		string s(x);
		Node* node = root;
		for(int i =0; i < s.length();++i){
			node = go(node, s[i]);
			Node* temp = node;
			while(temp != root){
			  if(temp->leaf){
				ada[temp->value] = 1;
			  }
			  temp = dictSuffLink(temp);
			}
		}
		
		for(int i = 0; i < ampas; i++) {
			if (ada[i]) cout << "y\n";
			else cout << "n\n";
		}
		
	}
	return 0;
}
 
