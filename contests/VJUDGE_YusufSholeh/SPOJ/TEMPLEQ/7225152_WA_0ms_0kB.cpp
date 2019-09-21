//Time sebelum : 500ms
//Nyoba pakai fast Input
//Nyoba pakai fast Output
//100 rb array dn 500 rb array, ngaruh besar? (gk tau jg sy :v)

#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

inline void fastRead_int(int &x) {
    register int c = getchar_unlocked();
    x = 0;
    for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());
    for(; c>47 && c<58 ; c = getchar_unlocked()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }
} 
inline void fastWrite_int(int x) {

    char S[22];
    register int c = 0;
    if(x<0){
        x = -x;
        putchar_unlocked('-');
    }

    for(;x;x/=10)S[c++]=x%10+48;
 
    while(c)putchar_unlocked(S[--c]);
    putchar_unlocked('\n');
} 

typedef pair<int,int> pii;

int n, q, X(0);
int que[MAX], bit[MAX], val[MAX];
pii arr[MAX];

inline void update(int x, int val) {
	for(; x <= n; x += (x & (-x)))
		bit[x] += val;
}

inline int query(int x) {
	int sum = 0;
	for(; x > 0; x -= (x&(-x)))
		sum += bit[x];
	return sum;
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
	fastRead_int(n);
	fastRead_int(q);
	for(int i = 1; i <= n; i++)
		fastRead_int(arr[i].first), arr[i].second = i;
	
	while((1 << X) <= n) X++; X--;
	
	sort(arr + 1, arr + n + 1);
	
	for(int i = 1; i <= n; i++) {
		val[i] = arr[i].first;
		que[arr[i].second] = i;
	}
	
	while(q--) {
		int op, a;
		fastRead_int(op);
		fastRead_int(a);
		if (op == 1) {
			int pos = que[a];
			int get_pos = UB(val[pos] + query(pos));
			update(get_pos-1,+1);
			update(get_pos  ,-1);
			swap(que[arr[get_pos-1].second], que[a]);
			swap(arr[get_pos-1].second, arr[pos].second);
		} else if (op == 2) fastWrite_int(n - UB(a-1) + 1);
		else update(UB(a-1), -1);
	}
}