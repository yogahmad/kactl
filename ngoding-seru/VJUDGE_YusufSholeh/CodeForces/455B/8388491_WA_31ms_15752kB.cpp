#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

int n, k;
string st[MAX];

class node{
public:
	node* letter[27];
	bool sengajaKalah, sengajaMenang;
};

node* root = NULL;

void insert(string ins) {
	int len = ins.length();
	node* cur = root;
	for(int i = 0; i < len; i++) {
		int newChar = (int)ins[i] - 'a';
		if (cur->letter[newChar] == NULL) {
			cur->letter[newChar] = new node();
		}
		cur = cur->letter[newChar];
	}
}

void dfsCalc(node* cur) {
	bool isLeaf = true;
	for(int i = 0; i < 27; i++) {
		if (cur->letter[i] != NULL) {
			isLeaf = false;
			dfsCalc(cur->letter[i]);
		}
	}
	
	if (isLeaf) {
		cur->sengajaKalah = false;
		cur->sengajaMenang = false;
	} else {
		bool existLose = false;
		bool existWin = false;
		for(int i = 0; i < 27; i++) {
			if (cur->letter[i] != NULL) {
				if (cur->letter[i]->sengajaMenang == false) {
					existLose = true;
				}
				if (cur->letter[i]->sengajaKalah == true) {
					existWin = true;
				}
			}
		}
		
		if (existLose) cur->sengajaMenang = true;
		else cur->sengajaMenang = false;
		if (existWin) cur->sengajaKalah = false;
		else cur->sengajaKalah = true;
	}
}

int main() {
	root = new node();
	
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> st[i];
		insert(st[i]);
	}
	
	dfsCalc(root);
	
	bool mustWin = root->sengajaMenang;
	bool mustLose = !root->sengajaKalah;
	// printf("%d %d\n",mustWin,mustLose);
	
	if (mustWin) {
		if (mustLose) {
			printf("First\n");
		} else {
			if (k % 2 == 1) printf("First\n");
			else printf("Second\n");
		}
	} else {
		if (mustLose) {
			printf("Second\n");
		} else {
			if (k % 2 == 1) printf("Second\n");
			else printf("First\n");
		}
	}
}