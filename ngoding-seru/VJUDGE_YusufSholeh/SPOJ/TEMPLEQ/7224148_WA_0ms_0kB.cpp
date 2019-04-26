#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

typedef pair<int,int> pii;

int n, q, X(0);
int que[MAX], bit[MAX], val[MAX];
pii arr[MAX];

inline void update(int x, int val) {
	for(; x <= n; x += (x & (-x)))
		bit[x] += val;
}

inline int UB(int k) {
	int sum = 0;
	int idx = 0;
	for(int i = X; i >= 0; i--) {
		idx += (1 << i);
		if (idx > n || val[idx] + sum + bit[idx] > k) idx -= (1 << i);
		else sum += bit[idx];
	}
	return idx+1;
}

int main() {
	scanf("%d %d",&n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d",&arr[i].first), arr[i].second = i;
	
	while((1 << X) <= n) X++; X--;
	
	sort(arr + 1, arr + n + 1);
	
	for(int i = 1; i <= n; i++) {
		val[i] = arr[i].first;
		que[arr[i].second] = i;
	}
	
	while(q--) {
		int op, a;
		scanf("%d %d",&op,&a);
		if (op == 1) {
			int pos = que[a];
			int get_pos = UB(arr[pos].first);
			update(get_pos-1,+1);
			update(get_pos  ,-1);
			arr[pos].first += 1;
		} else if (op == 2) printf("%d\n",n - UB(a-1) + 1);
		else update(UB(a-1), -1);
	}
}