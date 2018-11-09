/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: Implicit AVL. Delete array at index id1, and insert at indices id2. Preorder to restore the array.
 * Time: $O(Q \log N)$
 */

int n, x, id1, id2;
struct node{
	int key, height, size;
	struct node* left;
	struct node* right;
};
 
inline int getH(struct node *cur){
	if (cur == NULL) return 0;
	return cur -> height;
}
 
inline int getB(struct node* cur) {
	if (cur == NULL) return 0;
	return getH(cur->left) - getH(cur->right);
}
 
inline int getS(struct node* cur) {
	if (cur == NULL) return 0;
	return cur -> size;
}
 
inline void updateH(struct node* cur) {
	int a = getH(cur->left);
	int b = getH(cur->right);
	cur->height = ((a > b) ? a : b) +1;
}
 
inline void updateS(struct node* cur) {
	cur->size = 1 + getS(cur->left) + getS(cur->right);
}
 
inline struct node* newnode(int key) {
	struct node* cur = new node();
	cur -> key = key;
	cur -> left = NULL;
	cur -> right = NULL;
	cur -> height = 1;
	cur -> size = 1;
	return cur;
}
 
inline struct node* RotateRight(struct node* y) {
	struct node* x = y->left;
	struct node* xR = x->right;
	x->right = y;
	y->left = xR;
	updateH(y); updateH(x);
	updateS(y); updateS(x);
	return x;
}
 
inline struct node* RotateLeft(struct node* y) {
	struct node* x = y->right;
	struct node* xL = x->left;
	x->left = y;
	y->right = xL;
	updateH(y); updateH(x);
	updateS(y); updateS(x);
	return x;
}
 
struct node* minval(struct node* cur) {
	struct node* proc = cur;
	while(proc->left != NULL) proc=proc->left;
	return proc;
}
 
int value;
 
struct node* refresh(struct node* cur) {
	if (cur == NULL) return cur;
	updateH(cur); updateS(cur);
	int balance = getB(cur);
	if (balance > 1 && getB(cur->left) >= 0) return RotateRight(cur);
	if (balance > 1 && getB(cur->left) <  0) {cur->left = RotateLeft(cur->left); return RotateRight(cur);}
	if (balance <-1 && getB(cur->right) <= 0) return RotateLeft(cur);
	if (balance <-1 && getB(cur->right) > 0) {cur->right = RotateRight(cur->right); return RotateLeft(cur);}
	return cur;
}
struct node* DKTHS(struct node* cur, int K, bool left) {
	if (left) {
		if (cur -> left != NULL) cur -> left = DKTHS(cur -> left, K, left);
		else {
			struct node* temp = cur -> left? cur->left : cur -> right;
			if (temp == NULL) {
				temp = cur;
				cur = NULL;
			} else *cur = *temp;
			free(temp);
		}
	} else if (cur == NULL) return cur;
	else if (K <= getS(cur->left)) cur -> left = DKTHS(cur->left, K, 0);
	else if (K == getS(cur->left) + 1) {
		value = cur->key;
		if ((cur->left==NULL)||(cur->right==NULL)) {
			struct node* temp = cur -> left? cur->left : cur -> right;
			if (temp == NULL) {
				temp = cur;
				cur = NULL;
			} else *cur = *temp;
			free(temp);
		} else {
			node* temp = minval(cur->right);
			cur->key = temp->key;
			cur->right = DKTHS(cur->right, cur->key, 1);
		}
	} else cur -> right = DKTHS(cur->right, K - getS(cur->left) - 1, 0);
	return refresh(cur);
}
struct node* KTHS(struct node* cur, int K, bool left) {
	if (cur == NULL) return newnode(value);
	if (left) {
		if (cur == NULL) return newnode(value);
		else cur -> left = KTHS(cur->left, K, 1);
	}
	else if (K <= getS(cur->left)) cur -> left = KTHS(cur->left, K, 0);
	else if (K == getS(cur->left) + 1) {
		if (cur -> right == NULL) cur->right = KTHS(cur->right,K,0);
		else cur->right = KTHS(cur->right, K, 1);
	} else cur -> right = KTHS(cur->right, K - getS(cur->left) - 1, 0);
	return refresh(cur);
}
int cnt(0);
void preOrder(struct node* cur) {
	if (cur == NULL) return;
	preOrder(cur->left);
	A[++cnt] = cur->key;
	// printf("%d ",cur->key);
	preOrder(cur->right);
}

int main() {
	scanf("%d %d",&n, &x);
	struct node* root = NULL;
	for(int i = 1; i <= n; i++) {
		value = i;
		root = KTHS(root, i, 0);
	}
	for(int i = 1; i <= x; i++) {
		scanf("%d %d",&id1, &id2);
		root = DKTHS(root, id1, 0);
		root = KTHS(root, id2 - 1, 0);
	}
} 
