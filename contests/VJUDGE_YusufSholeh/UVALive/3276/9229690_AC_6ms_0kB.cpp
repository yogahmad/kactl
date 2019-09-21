#include<bits/stdc++.h>
using namespace std;

int W[505][505], N;
int mx[505], my[505]; // match arr
int lx[505], ly[505]; // label arr
int x[505], y[505]; // used arr
int hungary(int nd) {
    int i;
    x[nd] = 1;
    for(i = 1; i <= N; i++) {
        if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
            y[i] = 1;
            if(my[i] == 0 || hungary(my[i])) {
                my[i] = nd;
                return 1;
            }
        }
    }
    return 0;
}
int KM() {
    int i, j, k, d;
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for(i = 1; i <= N; i++)
        for(j = 1; j <= N; j++)
            lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];
    for(i = 1; i <= N; i++) {
        while(1) {
            memset(x, 0, sizeof(x));
            memset(y, 0, sizeof(y));
            if(hungary(i))  break;
            d = 0xfffffff;
            for(j = 1; j <= N; j++) {
                if(x[j]) {
                    for(k = 1; k <= N; k++)
                        if(!y[k])
                        d = d < lx[j]+ly[k]-W[j][k] ?
                            d : lx[j]+ly[k]-W[j][k];
                }
            }
            if(d == 0xfffffff)  break;
            for(j = 1; j <= N; j++) {
                if(x[j])    lx[j] -= d;
                if(y[j])    ly[j] += d;
            }
        }
    }
    int res = 0;
    for(i = 1; i <= N; i++) {
        if(my[i])
            res += W[my[i]][i];
    }
    return res < 0 ? 0 : res;
}

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int dist(pii a, pii b) {
	return abs(a.f - b.f) + abs(a.s - b.s);
}
pii arr[20];

int main() {
    int n, board = 0;
    while(scanf("%d", &n) && n) {
        N = n;
		int ans = -1;
		int ampas = 1e5;
        for(int i = 0; i < n; i++)
			scanf("%d %d",&arr[i].f, &arr[i].s);
        
        for(int x = 1; x <= n; x++) {
			for(int i = 0; i < n; i++) {
				for(int y = 1; y <= n; y++) {
					W[i+1][y] = ampas - dist(arr[i], mp(x, y));
					// if (x == 1) printf("%d %d %d\n",i+1, y, W[i+1][y]);
				}
			}
			ans = max(ans, KM());
		}
		
		for(int y = 1; y <= n; y++) {
			for(int i = 0; i < n; i++) {
				for(int x = 1; x <= n; x++) {
					W[i+1][x] = ampas - dist(arr[i], mp(x, y));
				}
			}
			ans = max(ans, KM());
		}
		
		for(int xx = 0; xx < 2; xx++) {
			for(int i = 0; i < n; i++) {
				for(int k = 1; k <= n; k++) {
					if (xx == 0) W[i+1][k] = ampas - dist(arr[i], mp(k,k));
					else W[i+1][k] = ampas - dist(arr[i], mp(n-k+1,k));
				}
			}
			ans = max(ans, KM());
		}
		
		printf("Board %d: %d moves required.\n\n",++board, ampas*n - ans);
    }
    return 0;
}