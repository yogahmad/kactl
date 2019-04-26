#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int NALPHABET = 26;

int FI[N];

struct Node {
  Node** children, **go;
  bool leaf;
  char charToParent;
  Node* parent, *suffLink, *dictSuffLink;
  int count, value, first;
 

  Node(){
    children = new Node*[NALPHABET];
    go = new Node*[NALPHABET];
    for(int i = 0; i < NALPHABET;++i){
      children[i] = go[i] = NULL;
    }
    parent = suffLink = dictSuffLink = NULL;
    leaf = false;
    count = 0;
  }
};
 
Node* createRoot() {
  Node* node = new Node();
  node->suffLink = node;
  return node;
}
 
void addString(Node* node, const string& s, int value =-1) {
  for(int i = 0; i < s.length(); ++i){
    int c = s[i] - 'a';
    if(node->children[c] == NULL){
      Node* n = new Node();
      n->parent = node;
      n->charToParent = s[i];
      node->children[c] = n;
    }
    node = node->children[c];
  }
  node->leaf = true;
  node->count++;
  if (node->count == 1) {
    node->first = value;
  }
  FI[value] = node->first;
  node->value = value;
}
 
Node* suffLink(Node* node);
Node* dictSuffLink(Node* node);
Node* go(Node* node, char ch);
int calc(Node* node);
 
Node* suffLink(Node* node) {
  if (node->suffLink == NULL){
    if (node->parent->parent == NULL){
      node->suffLink = node->parent;
    } else {
      node->suffLink = go(suffLink(node->parent),node->charToParent);
    }
  }
  return node->suffLink;
}
 
Node* dictSuffLink(Node* node) {
  if(node->dictSuffLink == NULL){
    Node* n = suffLink(node);
    if (node == n){
      node->dictSuffLink = node;
    } else {
      while (!n->leaf && n->parent != NULL){
        n = dictSuffLink(n);
      }
      node->dictSuffLink = n;
    }
  }
  return node->dictSuffLink;
}
 
Node* go(Node* node, char ch) {
  int c = ch -'a';
  if (node->go[c] == NULL){
    if (node->children[c] != NULL) {
      node->go[c]= node->children[c];
    } else {
      node->go[c]= node->parent == NULL? node : go(suffLink(node), ch);
    }
  }
  return node->go[c];
}

int calc(Node* node) {
  if (node->parent == NULL) {
    return 0;
  } else {
    return node->count + calc(dictSuffLink(node));
  }
}

int n, q;
int root[N];
int ans[N];
int day[N];
map<string,int> maps;
string s[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  Node* root = createRoot();

  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> s[i];
    addString(root, s[i], i);
  }

  int kur = 1;
  cin >> q;
  while(q--) {
    int typ;
    string p;
    cin >> typ;
    if (typ == 1) {
      cin >> p;
      Node *node = root;
      kur += 1;
      for(int i = 0; i < (int)p.length(); i++) {
        node = go(node, p[i]);
        Node *temp = node;
        while(temp != root) {
          if (temp -> leaf) {
            if (day[temp->first] != kur) {
              day[temp->first] = kur;
              ans[temp->first] += 1;
            }
            // cout << i << " " << temp->first << endl;
          }
          temp = dictSuffLink(temp);
        }
      }
    } else {
      int id;
      cin >> id;
      cout << ans[FI[id]] << endl;
    }
  }

  return 0;
}