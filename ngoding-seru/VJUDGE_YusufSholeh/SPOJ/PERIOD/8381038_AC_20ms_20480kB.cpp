#include<bits/stdc++.h>
using namespace std;
#define MAX 1000005

char pat[MAX];

int lps[MAX];
int n;

void makeLPS() {
	lps[0] = 0;
	int len = 0, i = 1;
	while(i < n) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		} else {
			if (len != 0) len = lps[len - 1];
			else lps[i++] = len; // reset lps[i] = 0
		}
	}
}

int main() {
	int tc;
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		if (cs > 1) printf("\n");
		
		scanf("%d",&n);
		scanf("%s",&pat);
		
		makeLPS();
		// for(int i = 0; i < n; i++) printf("%d %d\n",i, lps[i]);
		
		printf("Test case #%d\n",cs);
		for(int i = 1; i <= n; i++) {
			int back = lps[i-1];
			
			if (back >= (i+1)/2) {
				back = i - back;
				if (i % back != 0) continue;
				// printf("LPS %d %d\n",i-1,lps[i-1]);
				printf("%d %d\n",i, i/back);
			}
		}
	}
}