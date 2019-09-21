#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int bridge_no;

map<pii, int> maps;
map<int, int> deg[MAX];

int T[MAX];

vector<int> g[MAX];
bool used[MAX];
bool used2[MAX*2];
int timer, tin[MAX], fup[MAX];
int dp[MAX*2][2];
int n, m;
int region_no = 0;

void dfss (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfss (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v]) {
                ++bridge_no;
                maps[mp(v, to)] = -bridge_no;
                maps[mp(to, v)] = -bridge_no;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfss (i);
}

int patok = 0;

int dist(int a, int patok) {
    if (a >= patok) return a - patok;
    return n-1-patok + a + 1;
}

bool cmp(int a, int b) {
    return dist(a, patok) <= dist(b, patok);
}

vector<int> tree[MAX*2];
const int INF = 1e9;

void dfs(int now, int par) {
    int is_child = 0;
    for(int nxt : tree[now]) {
        if (nxt == par) continue;
        dfs(nxt, now);
        is_child += 1;
    }

    //dp[now][0] = 1 -> parent bunder tipe A diambil, 0 -> parent bunder tipe B gak diambil
    used2[now] = true;
    dp[now][0] = 0;
    dp[now][1] = 0;
    if (is_child == 0) {
        if (now > region_no + 1) { // TIPE B
            dp[now][1] = 0;
            dp[now][0] = INF;
        } else { // TIPE A
            dp[now][0] = 0;
            dp[now][1] = 0;
        }        
    } else {
        if (now > region_no + 1) { // TIPE B
            // dp[now][1] :    
            // dp[now][0], salah satu harus di ambil
            // printf("TIPE B %d\n",now);
            int semua_nol = 1;
            int mini = INF, jum = -1;
            for(int nxt : tree[now]) {
                if (nxt == par) continue;
                if (1+dp[nxt][1] <= dp[nxt][0]) { //ambil lebih murah dari pada biarin
                    semua_nol = 0;
                }
                if (1+dp[nxt][1]<mini) {
                    mini = 1+dp[nxt][1];
                    jum = -dp[nxt][0] + mini;
                }
                dp[now][1] += min(dp[nxt][0], 1+dp[nxt][1]);
                dp[now][0] += min(dp[nxt][0], 1+dp[nxt][1]);
                // printf("%d %d\n",dp[now][0], dp[now][1]);
            }
            if (semua_nol == 1) dp[now][0] += jum;
        } else { // TIPE A
            for(int nxt : tree[now]) {
                if (nxt == par) continue;
                dp[now][0] = dp[nxt][0];
                dp[now][1] = dp[nxt][1];
            }
        }
    }
    // printf("HAHA %d %d %d\n",now, dp[now][0], dp[now][1]);
}

int main() {
    memset(dp, -1, sizeof dp);
    while(scanf("%d %d",&n, &m) != EOF) {
        region_no = 1;
        bridge_no = 0;
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d",&u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
            maps[mp(u,v)] = 1;
            maps[mp(v,u)] = 1;
        }

        // cari bridge sebelum ditambahin i, i+1
        find_bridges();

        // adding i, i+1 edge buat bikin region
        for(int i = 0; i < n; i++) {
            int nxt = (i + 1)%n;
            if (maps.count(mp(i, nxt))) continue;
            ++region_no;
            maps[mp(i, nxt)] = region_no;
            maps[mp(nxt, i)] = region_no;
            g[i].push_back(nxt);
            g[nxt].push_back(i);
            T[i] = region_no;
        }

        for(int i = 0; i < n; i++) {
            patok = i;
            sort(g[i].begin(), g[i].end(), cmp);
            // printf("==================== %d\n",i);
            // for(int nxt : g[i]) { printf("%d ",nxt); }
            // printf("\n");
        }

        for(int i = 0; i < n; i++) {
            int sz = g[i].size();
            for(int j = 0; j < sz; j++) {
                int nxt = g[i][j];
                int tmp = j - 1;
                if (tmp == -1) tmp = sz - 1;
                deg[i][nxt] = tmp;
            }
        }

        // Todo case circle - 1

        int case_circle = 0;
        for(int start = 0; start < n; start++) {
            if (g[start].size() == 2) continue; case_circle += 1;
            int finish = start + 1;
            int ada_region = 0;
            for(int j = (start + 1)%n; ; j=(j+1)%n) {
                int nxt = j-1; if(nxt == -1) nxt = n-1;
                int tmp = maps[mp(j, nxt)];
                if (tmp > 1) ada_region = tmp;
                if (g[j].size() != 2) {
                    finish = j;
                    break;
                }
            }
            if (ada_region == 0) continue;
            // printf("start finish region %d %d %d\n",start, finish, region_no);
            for(int j = (start + 1)%n; ; j=(j+1)%n) {
                int nxt = j-1; if(nxt == -1) nxt = n-1;
                int tmp = maps[mp(j, nxt)];
                if (tmp < 0) {
                    int gg = region_no + 1 + abs(tmp);
                    tree[ada_region].push_back(gg);
                    tree[gg].push_back(ada_region);
                }
                if (j == finish) break;
            }
            // printf("%d %d %d\n",start, finish, ada_region);
            // bikin pulau
            int last = g[finish].size() - 2;
            int now = finish;
            // printf("%d\n",now);
            while(now != start) {
                int nxt = g[now][last];
                int tmp = maps[mp(now, nxt)];
                if (tmp < 0) { 
                    // printf("bridge\n"); 
                    int gg = region_no + 1 + abs(tmp);
                    tree[ada_region].push_back(gg);
                    tree[gg].push_back(ada_region);
                }
                // printf("%d\n",nxt);
                last = deg[nxt][now];
                now = nxt;
            }

            // printf("Node ============ %d\n",ada_region);
            // for(int node : tree[ada_region] ) {
                // printf("%d\n",node);
            // }s
        }
    
        if (case_circle == 0) {
            if (region_no == 1) printf("0\n");
            else printf("1\n");
        } else {
            // printf("TOT region %d\n",region_no);    

            int ans = 0;
            for(int i = region_no + 2; i < region_no + 1 + bridge_no + 1; i++) {
                if (used2[i]) continue;
                dfs(i, -1);
                ans += dp[i][0];
            }

            printf("%d\n",ans);
        }

        maps.clear();
        for(int i = 0; i < MAX; i++) {
            T[i] = 0;
            deg[i].clear();
            tree[i].clear(); 
            tree[MAX+i].clear();
            used2[i] = false;
            used2[MAX+i] = false;
            dp[i][0] = -1; dp[i][1] = -1;
            dp[MAX+i][0] = -1; dp[MAX+i][1] = -1;
            g[i].clear();
            tin[i] = 0;
        }
    }
}


