#include<bits/stdc++.h>
using namespace std;

#define MAX 1000005

bool prime[MAX];
int highest[MAX];

void generate_sieve() {
	prime[0] = true;
	prime[1] = true;
	prime[2] = false;
	int cnt = 0;
	for(int i = 2; i < MAX; i++) {
		if (!prime[i]) {
			highest[i] = i;
			for(int j = i+i; j < MAX; j += i) {
				if (highest[j] < i) highest[j] = i;
				prime[j] = true;
			}
		}
	}
}

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int fact[MAX];
int fact2[MAX];
int n, k;

void set_factor(int number) {
	// printf("NUMBER : %d\n",number);
	while(number > 1) {
		int v = highest[number];
		// printf("cur number : %d highest : %d\n",number, v);
		int cnt = 0;
		while(number % v == 0) {
			cnt += 1;
			number /= v;
		}
		fact2[v] = max(fact2[v], cnt);
		// printf("%d %d\n",v, cnt);
	}
}

int main() {
	generate_sieve();
	scanf("%d %d",&n, &k);
	set_factor(k);
	for(int i = 0; i < MAX; i++) fact[i] = fact2[i];
	memset(fact2, 0, sizeof(fact2));
	for(int i = 1; i <= n; i++) {
		int x; scanf("%d",&x);
		set_factor(x);		
	}
	
	for(int i = 0; i < MAX; i++) {
		if (fact[i] > 0 && fact[i] > fact2[i]) {
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}