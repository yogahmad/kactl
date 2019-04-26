#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1 << 21) + 5;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int n;
int l[MAXN], r[MAXN];

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; i++) scanf("%d %d",&l[i], &r[i]);
        queue<pii> q;
        q.push(mp(1, 1));
        while(!q.empty()) {
            pii now = q.front();
            q.pop();
            if (l[now.f] * r[now.f] == 0) {
                printf("%d\n",now.s);
                break;
            }
            q.push(mp(l[now.f], now.s + 1)); 
            q.push(mp(r[now.f], now.s + 1));
        }
    }
}