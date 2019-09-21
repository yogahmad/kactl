#include<bits/stdc++.h>
using namespace std;

const int MAX = 200005;

class Element_suffix{
public:
	int rank_now, rank_pref, pos;
};

class Suffix{
private:
	bool same_rank(Element_suffix a, Element_suffix b) {
		return a.rank_now == b.rank_now && a.rank_pref == b.rank_pref;
	}
	void reset_freq(bool is_sort_now) {
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
	void build_suffix(string s) {
		memset(sorted,0,sizeof(sorted));
		memset(SA,0,sizeof(SA));
		n = s.length();
		end = max(n, 1 << 8);
		for(int i = 0; i < n; i++) {
			sorted[0][i] = (int)s[i];
			if (s[i] == '{') {sorted[0][i] += n;}
		}
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
};


Suffix A;
int LCP[MAX], n;
int idx[MAX];
int day = 0;
int vis[MAX];
bool boleh[MAX];

bool coba(int H, int len) {
	int ret = 0;
	day++;
	for(int i = 0; i < len-1; i++) {
		if (boleh[i] && LCP[i] >= H) {
			int indx = idx[A.SA[i]];
			int indx2 = idx[A.SA[i+1]];
			if (vis[indx] != day) {
				vis[indx] = day;
				ret++;
			}
			if (vis[indx2] != day) {
				vis[indx2] = day;
				ret++;
			}
		} else {
			if (ret > n/2) {
				return true;
			}
			ret = 0;
			day++;
		}
	}
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tc = 0;	
	while(true) {
		cin >> n;
		if (n == 0) return 0;
		if (tc) cout << '\n';
		
		if (n == 1) {
			string s;
			cin >> s;
			cout << s << endl;
			tc++;
			continue;
		}
		
		string gabung = "";
		memset(idx,0,sizeof(idx));
		
		for(int i = 1; i <= n; i++) {
			string s;
			cin >> s;
			
			gabung += s;
			int sz = gabung.size();
			int len = s.size();
			for(int j = sz-1; j >= sz-len; j--) {
				idx[j] = i;
			}
			gabung += (char)((int)'z' + 1);
		}
		
		memset(boleh, 0, sizeof (boleh));
		
		// cout << gabung << endl;
		A.build_suffix(gabung);
		
		int len = gabung.length();
		
		for(int i = 0; i < len-1; i++) {
			if (isalpha(gabung[A.SA[i]])) boleh[i] = true;
			else boleh[i] = false;
			LCP[i] = A.compute_lcp(A.SA[i], A.SA[i+1]);
			// cout << i << " " << LCP[i] << " " << boleh[i] << endl;
		}
		
		int l = 1, r = 1000;
		int ans = -1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if (coba(mid, len)) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		
		// cout << "ANS " << ans << endl;
		if (ans == -1) cout << "?\n";
		else {
			set<string> st;
			day++;
			int ret = 0;
			for(int i = 0; i < len-1; i++) {
				if (boleh[i] && LCP[i] >= ans) {
					int indx = idx[A.SA[i]];
					int indx2 = idx[A.SA[i+1]];
					if (vis[indx] != day) {
						vis[indx] = day;
						ret++;
					}
					if (vis[indx2] != day) {
						vis[indx2] = day;
						ret++;
					}
				} else {
					if (ret > n/2) {
						// cout << ret << endl;
						string RETZ = "";
						for(int k = 0; k < ans; k++) {
							RETZ += gabung[A.SA[i-1]+k];
						}
						st.insert(RETZ);
					}
					ret = 0;
					day++;
				}
			}
			
			for(set<string>::iterator it = st.begin(); it != st.end(); it++) {
				cout << *it << endl;
			}
		}
		
		tc++;
	}
}