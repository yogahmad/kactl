#include<bits/stdc++.h>
using namespace std;


#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define pb push_back

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int ret;
	scanf("%d",&ret);
	return ret;
}

#define LL long long
#define MAX 100005


string s;
int dua[MAX];
int tiga[MAX];
int main(){
	int n;
	cin >> n;
	cin >> s;
	if (n <= 3) {
		cout << s << endl;
		return 0;
	}
	s = 'x'+s;
	for(int i = 1; i <= n; i++) {
		cout << s[i];
		if (i == n) break;
		if (i % 2 == 0) {
			if (i == n-1) continue;
			cout << '-';
		}
	}
	printf("\n"); return 0;
}
