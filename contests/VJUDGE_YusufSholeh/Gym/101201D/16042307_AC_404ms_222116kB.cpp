#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 305;
const int MOD = 1e9 + 7;

int n, k;
int t[N];
int dp[N][N][N][2];
ll fact[N];

int f(int kurang_x, int belum_x, int lebih_x, bool bol, int step, int x) {
  if (kurang_x < 0 || belum_x < 0 || lebih_x < 0) return 0;

  // printf("kurang_x %d ",kurang_x);
  // printf("belum_x %d ",belum_x);
  // printf("lebih_x %d bol %d ",lebih_x, bol);
  // printf("step %d\n",step);

  if (step >= k && kurang_x == 0 && bol) {
    ll res = n - (step - k + 1) + 1;
    res = (res * fact[max(0, lebih_x+belum_x)])%MOD;
    // printf("return %lld\n",res);
    return res;
  }

  if (step >= k) {
    if (kurang_x > 0) {
      kurang_x -= 1;
    }
  }

  int &ret = dp[kurang_x][belum_x][lebih_x][bol];
  if (ret >= 0) return ret;
  
  ret = 0;
  
  if (!bol) { // x masuk ke dalam k
    ret = f(kurang_x, belum_x, lebih_x, true, step + 1, x);
  }

  if (bol && belum_x == 0 && lebih_x == 0) {
    step += kurang_x + 1;
    // printf("HAA %d %d\n", step, k);
    ll res = n - (step - k + 1) + 1;
    res = (res * fact[max(0, lebih_x+belum_x)])%MOD;
    // printf("return %lld\n",res);
    return ret = res;
  }

  ret = ret + (1ll * belum_x * f(kurang_x + 1, belum_x - 1, lebih_x, bol, step + 1, x))%MOD;
  if (ret >= MOD) ret -= MOD;
  ret = ret + (1ll * lebih_x * f(kurang_x, belum_x, lebih_x - 1, bol, step + 1, x))%MOD;
  if (ret >= MOD) ret -= MOD;
  return ret;
}

int main() {
  fact[0] = 1;
  for(int i = 1; i < N; i++) fact[i] = (fact[i-1] * i)%MOD;

  scanf("%d %d",&n, &k);
  for(int i = 1; i <= n; i++) scanf("%d",&t[i]);
  sort(t + 1, t + n + 1);

  memset(dp, -1, sizeof dp);
  ll ans = 0;
  for(int i = 1; i <= n; i++) {
    // printf("mulai %d\n",i);
    // int j = i;
    // while(j < n && t[j+1] == t[i]) j++;
    ll kur = 0;
    kur = f(0, i-1, n-(i-1)-1, 0, 0, i);
    // printf("dapat %lld\n",kur);
    kur = (kur * t[i])%MOD;
    // kur = (kur * (j - i + 1))%MOD;
    ans = (ans + kur)%MOD;
    // i = j;
  }

  printf("%lld\n",ans);

  return 0;
}