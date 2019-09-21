#include <bits/stdc++.h>
using namespace std;

const int MAX = 1100;

int n, m, ox, oy(-1), tot(0);
int p[MAX][MAX];
char s[MAX][MAX];

bool calc(int sx, int sy, int ex, int ey) {
    return ((p[ex][ey] - p[ex][sy-1] - p[sx-1][ey] + p[sx-1][sy-1]) == ((ex - sx + 1) * (ey - sy + 1)));
}

int move(int x, int y, int lx, int ly) {
    if (calc(x + 1, y, x + lx, y + ly - 1)) return ly + move(x + 1, y, lx, ly);
    if (calc(x, y + 1, x + lx - 1, y + ly)) return lx + move(x, y + 1, lx, ly);
    return 0;
}

int main() {
    scanf("%d %d",&n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s",s[i]);
        for(int j = 0; j < m; j++) {
            if (s[i][j] == 'X') {
                if (oy == -1) ox = i, oy = j;
                tot += 1;
                p[i+1][j+1] = 1;
            }
            p[i+1][j+1] += p[i+1][j] + p[i][j+1] - p[i][j];
        }
    }
    int batki = ox+1, batka = oy+1;
    while(batka < m && s[ox][batka] == 'X') batka += 1;
    while(batki < n && s[batki][oy] == 'X') batki += 1;
    ox += 1, oy += 1;
    int dx = batki - ox + 1, dy = batka - oy + 1;

    int ans = 1e9;
    for(int i = 1; i <= dy; i++) {
        if (calc(ox, oy, batki, oy + i -1)) {
            if (move(ox, oy, dx, i) + dx * i == tot) {
                ans = min(ans, dx * i);
            }
        }
    }

    for(int i = 1; i <= dx; i++) {  
        if (calc(ox, oy, ox + i - 1, batka)) {
            if (move(ox, oy, i, dy) + dy * i == tot) {
                ans = min(ans, dy * i);
            }
        }
    }

    if (ans == 1e9) printf("-1\n"); else printf("%d\n",ans);
}