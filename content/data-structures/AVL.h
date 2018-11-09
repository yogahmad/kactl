/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: Not Implicit. insert, delete, count, kth
 */

node* insert(node* cur, int key) {
	if (cur == NULL) return newnode(key);
	if (key == cur -> key) return cur;
	if (key < cur -> key) cur -> left = insert(cur->left, key);
	else cur -> right = insert(cur->right, key);
	return balance(cur);
}
 
node* Delete(node* cur, int key) {
	if (cur == NULL) return cur;
	if (key < cur -> key) cur->left = Delete(cur->left, key);
	else if (key > cur -> key) cur->right = Delete(cur->right, key);
	else {
		if ((cur->left==NULL)||(cur->right==NULL)) {
			node* temp = cur -> left? cur->left : cur -> right;
			if (temp == NULL) {
				temp = cur;
				cur = NULL;
			} else *cur = *temp;
			free(temp);
		} else {
			node* temp = minval(cur->right);
			cur -> key = temp -> key;
			cur -> right = Delete(cur->right, temp->key);
		}
	}
	if (cur == NULL) return cur;
	updateH(cur); updateS(cur);
	return balance(cur);
}
 
int KTHS(node* cur, int K) {
	if (K <= getS(cur->left)) return KTHS(cur->left, K);
	else if (K == getS(cur->left) + 1) return cur->key;
	else return KTHS(cur->right, K - getS(cur->left) - 1);
}
 
int COUNT(node* cur, int K) { // how many <= K
	if (cur == NULL) return 0;
	if (K < cur->key) return COUNT(cur->left, K);
	else return getS(cur->left) + 1 + COUNT(cur->right, K);
}
