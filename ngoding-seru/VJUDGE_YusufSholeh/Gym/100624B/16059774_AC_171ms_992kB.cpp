#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

char s[N];
int suf[N];

int main() {
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		scanf("%s",s);
		int len = strlen(s);

		bool all_zero = true;

		for(int i = 0; i < len; i++) if (s[i] == '1') all_zero = false;

		if (all_zero || __builtin_popcount(len + 1) == 1) {
			printf("DIES\n");
			continue;
		}

		if (len % 2 == 0) {
			printf("LIVES\n");
			continue;
		}

		bool gjl_gnp = true;
		for(int i = 0; i < len; i++) {
			if ((i+1)%2 == 1) {
				if (s[i] != '1') gjl_gnp = false;
			} else {
				if (s[i] != '0') gjl_gnp = false;
			}
		}

		if (gjl_gnp) {
			printf("DIES\n");
			continue;
		}

		if (len % 4 == 1) {
			printf("LIVES\n");
			continue;
		}

		for(int i = 0; i < N; i++) suf[i] = 0;

		for(int i = len-1; i >= 0; i--) {
			int a = (s[i] == '1');
			suf[i] = a ^ suf[i+2];
		}

		int pang = 1;
		while(pang*2 <= len) {
			pang *= 2;
		}

		int ki = pang; int dki = -1;	
		int ka = pang; int dka = +1;

		bool gajadi = false;
		for(int i = 0; i < len; i++) {
			if ((suf[ki-1] ^ suf[ka+2-1]) == 1) {
				gajadi = true;
				break;
			}
			ki += dki;
			ka += dka;

			if (ki == 1) dki = 1;
			if (ka == len) dka = -1;
		}

		if (gajadi) printf("LIVES\n");
		else printf("DIES\n");

	}
  return 0;
}