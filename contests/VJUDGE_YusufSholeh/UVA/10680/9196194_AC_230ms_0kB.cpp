#include<bits/stdc++.h>
using namespace std;

#define MAX 1000005

bool bol[MAX];
int prime[MAX], top = 0;

void generate_sieve() {
	for(int i = 2; i < MAX; i++) {
		if (!bol[i]) {
			prime[++top] = i;
			for(int j = i+i; j < MAX; j+=i) {
				bol[j] = true;
			}
		}
	}
}

int main() {
	generate_sieve();
	int n;
	while(scanf("%d",&n) && n) {
		int lima = 0;
		int tmp = n;
		while(tmp >= 5) lima++, tmp/=5;
		
		int ans = 1;
		
		for(int i = 1; i <= top; i++) {
			if (i == 3) continue;
			tmp = n;
			int jml = 0;
			while(tmp >= prime[i]) jml++, tmp/=prime[i];
			tmp = n;
			
			if (i == 1) jml -= lima;
			
			for(int j = 1; j <= jml; j++) ans = (ans * prime[i]) % 10;
		}
		
		printf("%d\n",ans);
	}
	
	return 0;
}