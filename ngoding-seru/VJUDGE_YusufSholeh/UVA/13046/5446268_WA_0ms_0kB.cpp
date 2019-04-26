#include<bits/stdc++.h>
#define MAX 50
using namespace std;
typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair
pii bus1[MAX];
pii bus2[MAX];
int detik[MAX][MAX];
int detik2[MAX][MAX];
int n, m, tc;

typedef pair<int,pii> plp;
plp euclid(int a, int b) {
	int x = 1, y = 0;
	int xLast = 0, yLast = 1;
	int q, n , m , r;
	while(a != 0) {
		q = b / a;
		r = b % a;
		m = xLast - q * x;
		n = yLast - q * y;
		xLast = x, yLast = y;
		x = m, y = n;
		b = a, a = r;
	}
	return mp(b, mp(xLast, yLast));
}

int main() {
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%d",&n);
		for(int i = 1; i <= n; i++) {
			scanf("%d %d",&bus1[i].f, &bus1[i].s);
		} 
		bus1[n + 1] = bus1[1];
		scanf("%d",&m);
		for(int i = 1; i <= m; i++) {
			scanf("%d %d",&bus2[i].f, &bus2[i].s);
		}
		bus2[m + 1] = bus2[1];
		memset(detik,-1,sizeof(detik));
		int det = 0;
		for(int i = 1; i <= n; i++) {
			detik[bus1[i].f][bus1[i].s] = det;
			if (bus1[i].f == bus1[i + 1].f) {
				if (bus1[i].s < bus1[i + 1].s) {
					for(int j = bus1[i].s + 1; j <= bus1[i + 1].s; j++) {
						det++;
						detik[bus1[i].f][j] = det;
					}
				} else {
					for(int j = bus1[i].s - 1; j >= bus1[i + 1].s; j--) {
						det++;
						detik[bus1[i].f][j] = det;
					}
				}
			} else {
				if (bus1[i].f < bus1[i + 1].f) {
					for(int j = bus1[i].f + 1; j <= bus1[i + 1].f; j++) {
						det++;
						detik[j][bus1[i].s] = det;
					}
				} else {
					for(int j = bus1[i].f - 1; j >= bus1[i + 1].f; j--) {
						det++;
						detik[j][bus1[i].s] = det;
					}
				}
			}
		}
		memset(detik2, -1, sizeof(detik2));
		int det2 = 0;
		for(int i = 1; i <= n; i++) {
			detik2[bus2[i].f][bus2[i].s] = det2;
			if (bus2[i].f == bus2[i + 1].f) {
				if (bus2[i].s < bus2[i + 1].s) {
					for(int j = bus2[i].s + 1; j <= bus2[i + 1].s; j++) {
						det2++;
						detik2[bus2[i].f][j] = det2;
					}
				} else {
					for(int j = bus2[i].s - 1; j >= bus2[i + 1].s; j--) {
						det2++;
						detik2[bus2[i].f][j] = det2;
					}
				}
			} else {
				if (bus2[i].f < bus2[i + 1].f) {
					for(int j = bus2[i].f + 1; j <= bus2[i + 1].f; j++) {
						det2++;
						detik2[j][bus2[i].s] = det2;
					}
				} else {
					for(int j = bus2[i].f - 1; j >= bus2[i + 1].f; j--) {
						det2++;
						detik2[j][bus2[i].s] = det2;
					}
				}
			}
		}
		
		// printf("%d %d\n",det, det2);
		int minim = 1e9;
		int posx = -1, posy = -1;
		for(int i = 0; i < MAX; i++) {
			for(int j = 0; j < MAX; j++) {
				if (detik[i][j] >= 0 && detik2[i][j] >= 0) {
					int a = det;  int b = detik [i][j];
					int c = -det2; int d = detik2[i][j];
					int k = d - b;
					plp GG = euclid(a, c);
					// printf("new bus\n");
					// printf("%d %d %d %d\n",i, j, a, c);
					// printf("%d %d\n",d,b);
					if (k % GG.f == 0) {
						int gcd = GG.f;
						int x0 = GG.s.f * k / gcd;
						int y0 = GG.s.s * k / gcd;
						int k0 = c / gcd;
						int k1 = a / gcd;
						// printf("x0,y0 %d %d\n",x0,y0);
						// printf("k0,k1 %d %d\n",k0,k1);
						double z  = (double)(-x0)/(-k0);
						double zz = (double)(-y0)/k1;
						// printf("z,z %.2lf %.2lf\n",z,zz);
						int x = (-k0 < 0) ? round(floor(z)) : round(ceil(z));
						int y = (k1 < 0) ? round(floor(zz)) : round(ceil(zz));
						// printf("x, y %d %d\n",x,y);
						x = -x*k0 + x0;
						y = y*k1 + y0;
						// printf("x,y %d %d\n",x,y);
						x = a*x + b;
						y = (-c)*y + d;
						assert(x == y);
						int res = x;
						// printf("%d\n\n",res);
						if (res < minim) {
							minim = res;
							posx = i;
							posy = j;
						}
					} 
				}
			}
		}
		
		printf("Case %d: ",cs);
		if (minim == 1e9) printf("No Collision\n");
		else printf("%d %d\n",posx, posy);
		
	}
}	