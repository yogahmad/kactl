#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define MAXN 10005

char s[105];
int ans = 0;
int n;

struct node{
	int val;
	node* letter[27];
};

bool Type = false;
void insert(node* root, int val) {
	node* cur = root;
	int len = strlen(s);
	for(int i = 0; i < len; i++) {
		int new_char = (int)s[i] - 'A';
		if (cur->letter[new_char] == NULL) {
			cur->letter[new_char] = new node();
			cur->letter[new_char]->val = 0;
		}
		cur = cur->letter[new_char];
		if (Type == false)cur->val += val;
		else {
			if (cur->val > 0) {
				ans++;
				cur->val -= 1;
			}
		}
	}
}

int main() {
	while(true) {
		node* root = NULL;
		root = new node();
		scanf("%d",&n);
		if (n == -1) return 0;
		ans = 0;
		Type = false;
		for(int i = 1; i <= n; i++) {
			scanf("%s",s);
			insert(root, 1);
		}
		Type = true;
		for(int i = 1; i <= n; i++) {
			scanf("%s",s);
			insert(root, -1);
		}
		printf("%d\n",ans);
	}
}	