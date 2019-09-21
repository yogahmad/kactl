#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int has;
	scanf("%d",&has);
	return has;
}

#define pq priority_queue
#define rep(k,i,j) for(int k = (int)i;k<(int)j;k++)
#define repd(k,i,j) for(int k = (int)i;k>=(int)j;k--)
#define LL long long

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);

LL a, b;

inline bool LessThan(LL a, LL b, LL c, LL d) { // a/b < c/d ? a*d < c*b
	return a*d < c*b;
}

int main(){
	while(true) {
		scanf("%lld %lld",&a,&b);
		if (a == 1 && b == 1) return;
		LL a1 = 0, b1 = 1;
		LL a2 = 1, b2 = 1;
		LL a3 = 1, b3 = 0;
		
		while(a2 != a && b2 != b) {
			if (LessThan(a,b,a2,b2)) {
				LL na = a1 + a2;
				LL nb = b1 + b2;
				a3 = a2, b3 = b2;
				a2 = na;
				b2 = nb;
				printf("L");
			} else {
				LL na = a2 + a3;
				LL nb = b2 + b3;
				a1 = a2, b1 = b2;
				a2 = na;
				b2 = nb;
				printf("R");
			}
		}
		printf("\n");
	}
}