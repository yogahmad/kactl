#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define f first
#define s second
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

#define LL long long
#define MAX 100005
#define MAXE 250005


double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);


int n, m;
int arr[505][505];
int nilai[505][505];

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		scanf("%d %d",&n, &m);
		
		int x, y;
		int sum1 = 0;
		int sum2 = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%d",&arr[i][j]);
				if (arr[i][j] == -1) x = i, y = j, nilai[i][j] = 0;
				else nilai[i][j] = arr[i][j];
				if ( (i + j)%2 == 0 ) {
					sum1 += nilai[i][j];
				} else {
					sum2 += nilai[i][j];
				}
				
				
			}
		}
		
		printf("%d\n",abs(sum1 - sum2));
	}
}