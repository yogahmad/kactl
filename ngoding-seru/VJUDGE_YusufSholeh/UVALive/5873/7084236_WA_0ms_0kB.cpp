#include<bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define MAX 100005
#define MAXC 1000005
using namespace std;

int tc;
bool bolx[MAXC+MAXC];
bool boly[MAXC+MAXC];

int main() {
	scanf("%d",&tc);
	while(tc--) {
		int t, p;
		scanf("%d %d",&t, &p);
		
		memset(bolx, false, sizeof(bolx));
		memset(boly, false, sizeof(boly));
		
		for(int i = 1; i <= t; i++) {
			int x, y;
			scanf("%d %d",&x, &y);
			bolx[x + MAXC] = true;
			boly[y + MAXC] = true;
		}
	
		for(int i = 1; i <= p; i++) {
			char op;
			int val;
			getchar();
			scanf("%c %d",&op, &val);
			
			//printf("ASDASDA %c %d\n",op, val);
			if (op == 'H' && boly[val + MAXC])
				assert(false);
			if (op == 'V' && bolx[val + MAXC])
				assert(false);
		}
	}
}