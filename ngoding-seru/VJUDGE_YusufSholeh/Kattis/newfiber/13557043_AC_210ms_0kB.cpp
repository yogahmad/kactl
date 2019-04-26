#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int n, m;
int tot[N];
pii arr[N];

int par[N];

int find(int x) {
	if (par[x] == x) return x;
	return par[x] = find(par[x]);
}

void join(int a, int b) {
	int u = find(a);
	int v = find(b);
	par[u] = v;
}

int main() {
	scanf("%d %d",&n, &m);
	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d",&a, &b);
		tot[a] += 1;
		tot[b] += 1;
	}

	for(int i = 0; i < n; i++) {
		arr[i] = {tot[i], i};
	}

	sort(arr, arr + n);


	
	for(int i = 0; i < n; i++) {
		par[i] = i;
	}

	int jml = 0;
	vector<pii> ans;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			// printf("%d %d\n",i, j);
			// printf("gg %d %d\n",arr[i].second, arr[j].second);
			int u = find(arr[i].second);
			int v = find(arr[j].second);
			// printf("jadi\n");
			if (u == v) continue;
			if (arr[j].first == 1 && j == n-1) {
				ans.push_back(make_pair(arr[i].second, arr[j].second));
				arr[i].first -= 1;
				arr[j].first -= 1;
				join(v, u);
			} else if (arr[j].first != 1) {
				ans.push_back(make_pair(arr[i].second, arr[j].second));
				arr[i].first -= 1;
				arr[j].first -= 1;
				join(v, u);
			}
			if (arr[i].first == 0) break;
		}
	}

	for(int i = 0; i < n; i++) if (arr[i].first == 0) jml += 1;

	printf("%d\n",n - jml);
	printf("%d %d\n",n, n-1);
	for(pii gg : ans) {
		printf("%d %d\n",gg.first, gg.second);
	}

	return 0;
}