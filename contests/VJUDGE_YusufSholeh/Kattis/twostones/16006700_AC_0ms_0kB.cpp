#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int main() {
	int n;
	scanf("%d",&n);
	if (n % 2 == 0) {
		printf("Bob\n");
	} else {
		printf("Alice\n");
	}
	return 0;
}