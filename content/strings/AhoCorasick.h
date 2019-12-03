/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick tree is used for dictionary matching.
 * Initialize the tree like the example at main below.
 * Time: Function create is $O(26N)$ where $N$ is the sum of length of patterns.
 * Becareful if the pattern allow duplicate. If not, the worst case is $N \sqrt N$.
 * Status: lightly tested
 */
#pragma once

const int N = 1e5 + 5;
 
struct AhoCorasick {
	int trie[N][26];
	int fail[N];
	int saiz;
 
	AhoCorasick() {
		memset(trie[0],-1,sizeof trie[0]);
		saiz = 0;
	}
 
	void add(string str) {
		int cur = 0;
		for(int i = 0 ; i < str.length() ; i++) {
			//checkChar(str[i]);
			int nex = str[i] - 'a';
			if(trie[cur][nex] == -1) {
				trie[cur][nex] = ++saiz;
				memset(trie[saiz],-1,sizeof trie[saiz]);
			}
			cur = trie[cur][nex];
		}
	}
 
	void build() {
		queue<int> q;
		fail[0] = 0;
 
		for(int i = 0 ; i < 26 ; i++)
			if(trie[0][i] == -1)
				trie[0][i] = 0;
			else {
				int nex = trie[0][i];
				fail[nex] = 0;
				q.push(nex);
			}
 
		while(!q.empty()) {
			int now = q.front();
			q.pop();
 
			for(int i = 0 ; i < 26 ; i++)
				if(trie[now][i] == -1)
					trie[now][i] = trie[fail[now]][i];
				else {
					int nex = trie[now][i];
					fail[nex] = trie[fail[now]][i];
					q.push(nex);
				}
		}	
	}
 
	int getIndex(string str) {
		int cur = 0;
		for(int i = 0 ; i < str.length() ; i++) {
			//checkChar(str[i]);
			cur = trie[cur][str[i] - 'a'];
		}
		return cur;
	}
 
};
