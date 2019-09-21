#include<bits/stdc++.h>
using namespace std;

const int MAX = 100005;

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
		n = s.length();
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
		// for(int i = 0; i < n; i++) {
			// printf("%d %d\n",i, SA[i]);
		// }
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	string tmp;
	cin >> tmp;
	A.build_suffix(tmp);
	
	int n = tmp.length();
	
	int q; cin >> q;
	while(q--) {
		string s;
		cin >> s;
		
		int len = s.length();
		int L = 0, R = n-1;
		for(int i = 0; i < len; i++) {
			
			// cout << i << " " << L << " " << R << endl;
			int l = L;
			int r = R;
			int ans = n;
			bool semua = true;
			while(l <= r) {
				int mid = (l + r) >> 1;
				int len_mid = n - A.SA[mid];
				if (len_mid < i+1) {
					l = mid + 1;
				} else {
					if (tmp[A.SA[mid]+i] >= s[i]) {
						semua = false;
						ans = mid;
						r = mid - 1;
					} else {
						l = mid + 1;
					}
				}
			}
			if (semua) {
				if (R == n - 1) {
					cout << "-1\n";
					goto found;
				}
				int lcp_next = A.compute_lcp(A.SA[R], A.SA[R+1]);
				int id = A.SA[R+1];
				for(int i = 0; i <= lcp_next; i++) cout << tmp[id+i];
				cout << "\n";
				goto found;
			}
			if (tmp[A.SA[ans]+i] > s[i]) {
				for(int j = 0; j < i; j++) cout << s[j];
				cout << tmp[A.SA[ans]+i] << endl;
				goto found;
			}
			L = ans;
			l = L;
			r = R;
			ans = n;
			while(l <= r) {
				int mid = (l + r) >> 1;
				int len_mid = n - A.SA[mid];
				if (len_mid < i+1) {
					l = mid + 1;
				} else {
					if (tmp[A.SA[mid]+i] > s[i]) {
						r = mid - 1;
					} else {
						ans = mid;
						l = mid + 1;
					}
				}
			}
			R = ans;
		}
		if (n - A.SA[L] == len) {
			if (L == n-1) cout << "-1\n";
			else {
				int lcp_next = A.compute_lcp(A.SA[L], A.SA[L+1]);
				int id = A.SA[L+1];
				for(int i = 0; i <= lcp_next; i++) cout << tmp[id+i];
				cout << "\n";
			}
		} else {
			int id = A.SA[L];
			for(int i = 0; i <= len; i++) cout << tmp[id+i]; 
			cout << "\n";
		}
		
		found:;
		// cout << "AMPAS " << s << endl;
	}
}