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
	int sorted[20][MAX], freq[MAX], start[MAX], SA[MAX], end, n, ceentete;
	Element_suffix suf[MAX], tmp[MAX];
	void build_suffix(string s) {
		memset(sorted,0,sizeof(sorted));
		memset(SA,0,sizeof(SA));
		n = s.length();
		end = max(n, 100000);
		ceentete = 1;
		for(int i = 0; i < n; i++) {
			sorted[0][i] = (int)s[i];
			if (s[i] == '{') {sorted[0][i] += ceentete++;}
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
		// for(int i = 0; i < n; i++) cout << i << " X " << SA[i] << endl;
	}
	int compute_lcp(int x, int y) {
		int ans = 0;
		for(int k = 19; k >= 0; k--) {
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
string gabung;
int total_length = 0;
int n, q;
int idx[MAX];

struct Input{
	int pos;
	string str;
	Input(){};
	Input(int _pos, string _str) {
		pos = _pos;
		str = _str;
	}
};

string que[MAX];
Input inp[MAX];
vector<Input> v[MAX];
vector<Input> G[100];

inline int get_val(char x) {
	return (int)x - 'a';
}

void radix_sort(int idx) {
	int size = v[idx].size();
	if (size == 0) return;
	for(int len = 0; len < idx; len++) {
		for(int i = 0; i < size; i++) {
			G[get_val(v[idx][i].str[idx-len-1])].push_back(v[idx][i]);
		}
		int TP = 0;
		for(int i = 0; i < 27; i++) {
			int size = G[i].size();
			for(int j = 0; j < size; j++) {
				v[idx][TP++] = G[i][j];
			}
			G[i].clear();
		}
		// cout << idx << " " << len << " " << TP << endl;
	}
}

typedef pair<int,int> pii;
typedef pair<int,pii> pip;
#define f first
#define s second
#define mp make_pair
int where[MAX];

pip Search(string s, int ID) {
	int len = s.length();
	// cout << "SEARCH " << s << " " << ID << endl;
	int L = 0, R = total_length;
	int N = gabung.length();
	for(int i = 0; i < len; i++) {
		int l = L, r = R, ans = N;
		bool ada = false;
		while(l <= r) {
			int mid = (l + r) >> 1;
			int len_mid = N - A.SA[mid];
			if (len_mid < i+1) {
				l = mid + 1;
			} else {
				char tmp = gabung[A.SA[mid]+i];
				if (tmp >= s[i]) {
					if (tmp == s[i]) ada = true;
					ans = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
		}
		
		if (ada == false) return mp(-1,mp(-1, ID));
		
		L = ans;
		l = L; r = R; ans = N;
		while(l <= r) {
			int mid = (l + r) >> 1;
			int len_mid = N - A.SA[mid];
			if (len_mid < i+1) {
				l = mid + 1;
			} else {
				if (gabung[A.SA[mid]+i] > s[i]) {
					r = mid - 1;
				} else {
					ans = mid;
					l = mid + 1;
				}
			}
		}
		R = ans;
	}
	return mp(L, mp(R, ID));
}

vector<int> merge(vector<int> &L, vector<int> &R) {
	int sz1 = L.size();
	int sz2 = R.size();
	
	vector<int> ret;
	int ptr1 = 0, ptr2 = 0, top = 0;
	
	while(true) {
		if (top == 10 || (ptr1 == sz1 && ptr2 == sz2)) break;
		if (ptr1 == sz1) {
			ret.push_back(R[ptr2]); top++; ptr2++;
		} else if (ptr2 == sz2) {
			ret.push_back(L[ptr1]); top++; ptr1++;
		} else {
			if (L[ptr1] <= R[ptr2]) ret.push_back(L[ptr1]), top++, ptr1++;
			else ret.push_back(R[ptr2]), top++, ptr2++;
		}
		if (top > 1 && ret[top-1] == ret[top-2]) {
			ret.pop_back();
			top--;
		}
	}
	
	return ret;
}

vector<int> tree[4*MAX];

void build(int now, int l, int r) {
	if (l == r) {
		tree[now].push_back(where[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	tree[now] = merge(tree[now<<1], tree[now<<1|1]);
}

vector<int> query(int now, int l, int r, int a, int b) {
	vector<int> ret;
	if (a > r || b < l) return ret;
	if (a <= l && r <= b) return tree[now];
	int mid = (l + r) >> 1;
	ret = query(now<<1,l,mid,a,b);
	vector<int> right = query(now<<1|1,mid+1,r,a,b);
	return merge(ret, right);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int tc = 0;	
	cin >> n;
	
	gabung = "";
	
	for(int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		int len = s.length();
		v[len].push_back(Input(i, s));
	}
	
	for(int i = 1; i < MAX; i++) {
		radix_sort(i);
	}
	
	int TP = 0;
	for(int i = 1; i < MAX; i++) {
		int size = v[i].size();
		for(int j = 0; j < size; j++) {
			inp[++TP] = v[i][j];
		}
	}
	
	// for(int i = 1; i <= n; i++) {
		// cout << inp[i].str << " " << inp[i].pos << endl;
	// }
	
	for(int i = 1; i <= n; i++) {
		string s = inp[i].str;
		gabung += s;
		int sz = gabung.size();
		int len = s.size();
		total_length += len;
		for(int j = sz-1; j >= sz-len; j--) idx[j] = i;
		gabung += '{';
	}
	
	A.build_suffix(gabung);
	
	int len = gabung.length();
	
	for(int i = 0; i < len; i++) {
		int pos = A.SA[i];
		if (i < total_length) assert(idx[pos] > 0);
		else assert(idx[pos] == 0);
		if (idx[pos] != 0) where[i] = idx[pos];
	}
	
	build(1, 0, total_length);
	
	cin >> q;
	for(int i = 1; i <= q; i++) {
		string s;
		cin >> s;
		pip ret = Search(s, i);
		
		// cout << ret.first << " " << ret.second.first << endl;
		
		// for(int i = ret.first; i <= ret.second.first; i++) {
			// cout << i << " " << inp[where[i]].pos << endl;
		// }
		
		if (ret.first == -1) {
			printf("-1\n");
		} else {
			vector<int> res = query(1, 0, total_length, ret.f, ret.s.f);
			int size = res.size();
			for(int i = 0; i < size; i++) {
				if (i == size-1) printf("%d\n",inp[res[i]].pos);
				else printf("%d ",inp[res[i]].pos);
			}
		}
	}
	
	
}