#include<bits/stdc++.h>
#define MAX 1000010
using namespace std;
struct node{
	int val;
	node* left, right;
	inline node (int val, node* left, node* right) :
		val(val), left(left), right(right) {}
};
node* root[MAX];
node* insert(node* cur, int l, int r, int v) {
	if (cur == NULL) cur = new node(0, NULL, NULL);
	if (v < l || v > r) return cur;
	node* nod = NULL;
	if (l == r) {
		nod = new node(cur -> val + 1, NULL, NULL);
	} else {
		int mid = (l + r) >> 1;
		nod = new node(cur -> val + 1, insert(cur->left, l, mid, v), insert(cur->right, mid + 1, r, v));
	}
	return cur = nod;
}

inline int c(node* now) {
	if (now == NULL) return 0;
	return now -> val;
}
int query(node* u, node* v, int l, int r, int z) {
	if (l == r) {
		if (z <= l) return 0;
		return v -> val - u -> val;
	}
	int m = (l + r) >> 1;
	if (z > m-1) { // query kurang dari m
		return c(v -> left) - c(u -> left) + query(u -> right, v -> right, m + 1, r, z);
	}
	return query(u -> left, v -> left, l, m, z);
}
node* build(node* cur, int l, int r) {
	if (cur == NULL) cur = new node(0, NULL, NULL);
	if (l == r) {
		return cur = new node(0, NULL, NULL);
	} 
	int mid = (l + r) >> 1;
	cur -> left = build(cur->left,l,mid);
	cur -> right = build(cur->right,mid+1,r);
	return cur;
}

int main() {

	// for(int i = 0; i < MAX; i++) last2[0] = new node(0, NULL, NULL);
	root[0] = new node(0, NULL, NULL);
	root[0] = build(root[0], 1, MAX - 1);
	scanf("%d",&m); size = 0;
	while(m--) {
		scanf("%d %d %d %d",&op, &l, &r, &k);
		if (op == 0) {
			size++;
			root[size] = insert(root[size-1], 1, MAX - 1, k);
			// if (root[size] == NULL) printf("sdadsa\n");
		} else if (op == 2) {
			size -= k;
		} else {
			// printf("%d %d\n",l,r);
			int ans = query(root[l - 1], root[r], 1, MAX - 1, k);
			printf("%d\n",ans);
		}
	}
}