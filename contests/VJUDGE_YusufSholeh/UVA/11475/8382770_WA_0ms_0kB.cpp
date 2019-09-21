#include<bits/stdc++.h>
using namespace std;
#define MAX 1000005
char pat[MAX];
int n,lps[MAX];
inline int inverse(int x) {return n-1-x;};
void makeLPS() {
	lps[0] = n-1;
	int len = n-1, i = 0;
	while(i < n) {
		if (pat[i] == pat[len]) {
			lps[i] = len--;
			i++;
		} else {
			if (len != n-1) len = lps[inverse(len) - 1];
			else lps[i++] = len;
		}
	}
}
int main() {
	while(scanf("%s",pat) != EOF) {
		n = strlen(pat);
		makeLPS();		
		printf("%s",pat);
		for(int i = lps[n-1]-1; i >= 0; i--) printf("%c",pat[i]);
		printf("\n");
	}
}