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
#define INF 10000000

unsigned long long n;
unsigned long long a, b;

int main(){
	cin >> n;
	a = 1, b = 2;
	int ans = 0;
	while(a <= n) {
		unsigned long long c = b;
		b = a + b;		
		a = c;
		ans++;
	}
	printf("%d\n",ans-1);
}
