#include<bits/stdc++.h>
using namespace std;

const int NALPHABET = 26;

struct Node{
	Node** children;
	Node** go;
	bool leaf;
	char charToParent;
	Node* parent;
	Node* suffLink;
	Node* dictSuffLink;
	int count, value;
	int tambah;
	vector<int> anse;
	
	Node() {
		children = new Node*[NALPHABET];
		go = new Node*[NALPHABET];
		for(int i = 0; i < NALPHABET; i++) {
			children[i] = go[i] = NULL;
		}
		parent = suffLink = dictSuffLink = NULL;
		leaf = false;
		count = 0;
		tambah = 0;
	}
};

Node* createRoot() {
	Node* node = new Node();
	node->suffLink = node;
	return node;
}

Node* ptr[50000];
int global = 0;

void addString(Node* node, const string &s, int value = -1) {
	int sz = (int)s.length();
	for(int i = 0; i < sz; i++) {
		int c = s[i] - 'a';
		if (node->children[c]==NULL){
			Node* n = new Node();
			n -> parent = node;
			n -> charToParent = s[i];
			node -> children[c] = n;
		}
		node = node->children[c];
	}
	
	node->leaf = true;
	node->count++;
	node->value = value;
	node->anse.push_back(value);
	ptr[global++] = node;
}

Node* suffLink(Node* node);
Node* dictSuffLink(Node* node);
Node* go(Node* node, char ch);
int calc(Node* node);

Node* suffLink(Node* node) {
	if (node->suffLink == NULL) {
		if (node->parent->parent==NULL) {
			node->suffLink = node->parent;
		} else {
			node->suffLink = go(suffLink(node->parent), node->charToParent);
		}
	}
	return node->suffLink;
}

Node* dictSuffLink(Node* node){ 
	if (node->dictSuffLink == NULL) {
		Node* n = suffLink(node);
		if (node == n) {
			node->dictSuffLink = node;
		} else {
			while(!n->leaf && n->parent != NULL) {
				n = dictSuffLink(n);
			}
			node->dictSuffLink = n;
		}
	}
	return node->dictSuffLink;
}

Node* go(Node* node, char ch) {
	int c = ch-'a';
	if (node->go[c]==NULL) {
		if (node->children[c]!=NULL) {
			node->go[c] = node->children[c]; 
		} else {
			node->go[c] = node->parent == NULL? node : go(suffLink(node), ch);
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

int ans[50000];
int new_str[50000];

void traverse(Node* node) {
	for(int i = 0; i < NALPHABET; i++) {
		if (node->children[i]!=NULL){
			//printf("AMPAS\n");
			Node* next = node->children[i];
			int sz = next->anse.size();
			//for(int j = 0; j < sz; j++) ans[next->anse[j]] += next->tambah;
			//printf("ASD %d\n",next->tambah);
			traverse(next);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	Node* root = createRoot();
	int A, B, Q;
	cin >> Q >> A >> B;
	for(int i = 0; i < Q; i++) {
		string x; cin >> x;
		addString(root, x, i);
	}
	
	Node* node = root;
	int len = s.length();
	for(int i = 0; i < len; i++) {
		node = go(node, s[i]);
		Node* temp = node;
		while(temp != root) {
			if (temp->leaf) {
				temp->tambah += 1;
				//printf("WOAH %d\n",temp->tambah);
			}
			temp = dictSuffLink(temp);
		}
	}
	
	traverse(root);
	
	for(int i = 0; i < Q; i++) {
		cout << ptr[i]->tambah << endl;
		int new_char = (A * ans[i] + B)%26;
		node = go(node, (char)(new_char + 'a'));
		Node* temp = node;
		while(temp != root) {
			if (temp->leaf) {
				temp->tambah += 1;
				
			}
			temp = dictSuffLink(temp);
		}
	}
}
