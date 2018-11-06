/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Compute Suffix Array of Strings.
 * Usage:
 * compute_lcp(x,y) run in log N.
 * buildlcp() run in N and return lcp[i] = lcp SA[i] and SA[i-1].
 * Time: $O(|N| \log |N|)$
 */
#pragma once

class Element_suffix{
public:
  int rank_now, rank_pref, pos;
};

class Suffix{
private:
  inline bool same_rank(Element_suffix a, Element_suffix b) {
    return a.rank_now == b.rank_now && a.rank_pref == b.rank_pref;
  }
  inline void reset_freq(bool is_sort_now) {
    for(int i = 0; i <= end; i++) freq[i] = 0;
    for(int i = 0; i < n; i++) freq[ is_sort_now ? suf[i].rank_now+1 : suf[i].rank_pref+1 ]++;
    start[0] = 0;
    for(int i = 1; i <= end; i++) {
      start[i] = freq[i-1];
      freq[i] += freq[i-1];
    }
  }
public:
  int sorted[20][MAX], freq[MAX], start[MAX], SA[MAX], end, n;
  Element_suffix suf[MAX], tmp[MAX];
  void build_suffix() {
    n = strlen(s);
    if (n == 1) {
      SA[0] = 0;
      return;
    }
    end = max(n, 1 << 8);
    for(int i = 0; i < n; i++) sorted[0][i] = (int)s[i];
    int step = 1;
    for(int cnt = 1; cnt < n; step++, cnt *= 2) {
      for(int i = 0; i < n; i++) {
        suf[i].rank_pref = sorted[step-1][i];
        suf[i].rank_now = (i + cnt < n) ? sorted[step-1][i+cnt] : -1;
        suf[i].pos = i;
      }
      reset_freq(1);
      for(int i = 0; i < n; i++) tmp[start[suf[i].rank_now+1]++] = suf[i];
      reset_freq(0);
      for(int i = 0; i < n; i++) suf[start[tmp[i].rank_pref+1]++] = tmp[i];
      for(int i = 0; i < n; i++) {
        sorted[step][suf[i].pos] = (i && same_rank(suf[i], suf[i-1])) ? sorted[step][suf[i-1].pos] : i;
      }
    } step--;
    for(int i = 0; i < n; i++) SA[sorted[step][i]] = i;
  }
};
int compute_lcp(int x, int y) {
  int ans = 0;
  for(int k = 20; k >= 0; k--) {
    int s = (1 << k);
    if (x + s - 1 < n && y + s - 1 < n && sorted[k][x] == sorted[k][y]) {
      ans += s;
      x += s;
      y += s;
    }
  }
  return ans;
}
void buildLCP(){
    phi[SA[0]] = -1;
    for(int i = 1 ; i < len ; i++)
        phi[SA[i]] = SA[i - 1];
    for(int i = 0, l = 0 ; i < len ; i++){
        if(phi[i] == -1)
            PLCP[i] = 0;
        else{
            while(s[i + l] == s[phi[i] + l]) l++;
            PLCP[i] = l;
            l = max(0,l - 1);
        }    
    }
    for(int i = 0 ; i < len ; i++)
        LCP[i] = PLCP[SA[i]];
}
