#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define f first
#define s second
#define mp make_pair

const int N = 2e5 + 5;

string s1, s2;

int len, len1, len2;
int pref[N][28][2];

bool sama_char(int l1, int r1, int l2, int r2) {
	//printf("XX %d %d %d %d\n",l1, r1, l2, r2);
	for(int j = 0; j < 27; j++) {
		int atas = pref[r1][j][0] - pref[l1-1][j][0];
		int bawah = pref[r2][j][1] - pref[l2-1][j][1];
		if (atas != bawah) {
			//printf("gagal at %d\n",j);
			//printf("nilai %d %d\n",atas, bawah);
			return false;
		}
	}
//	printf("AHA\n");
	return true;
}

bool equivalent(int l1, int r1, int l2, int r2) {
	bool sama = true;
	int ptr = l2;
	for(int i = l1; i <= r1; i++) {
		if (s1[i] != s2[ptr]) {
			sama = false;
		}
		ptr += 1;
	}
	

	
	if (sama) return true;
	
	
	int pjg = (r1 - l1 + 1) % 2;
	if (!sama && pjg == 1) return false;
	
	// printf("%d %d %d %d\n",l1, r1, l2, r2);
	
	int mid1 = (l1 + r1)/2;
	int mid2 = (l2 + r2)/2;
	
	bool ada = false;
	if (sama_char(l1, mid1, l2, mid2) && sama_char(mid1+1, r1, mid2+1,r2)) {
		ada = (equivalent(l1, mid1, l2, mid2) && equivalent(mid1+1, r1, mid2+1, r2));
		if (ada) return true;
	} 
	if (sama_char(l1, mid1, mid2+1,r2) && sama_char(mid1+1,r1, l2, mid2)) {
		return equivalent(l1, mid1, mid2+1, r2) && equivalent(mid1+1, r1, l2, mid2);
	}
	return false;
}

int main() {
	cin >> s1;
	cin >> s2;
	
	s1 = '+' + s1;
	s2 = '+' + s2;
	
	len = s1.length();
	len1 = s1.length();
	len2 = s2.length();
	
	for(int i = 1; i < len1; i++) {
		pref[i][s1[i]-'a'][0] += 1;
		
		
		pref[i][s2[i]-'a'][1] += 1;
		
		
		for(int j = 0; j < 26; j++) {
			pref[i][j][1] += pref[i-1][j][1];
			pref[i][j][0] += pref[i-1][j][0];
		}
	}
	
	
	if (equivalent(1, len1-1, 1, len2-1)) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
	return 0;
}