#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int N = 1e3 + 5;
int n;


bool ask(int a, int b) {
	printf("1 %d %d\n",a, b);
	fflush(stdout);
	char s[10];
	scanf("%s",&s);
	if (s[0] == 'Y') return true;
	else return false;
}

// vector<int> res;

// void solve(vector<int> v) {
// 	int sz = v.size();
// 	if (v.size() == 1) {
// 		res.push_back(v[0]);
// 		return;
// 	} else if (v.size() == 0) {
// 		return;
// 	}


// 	int piv = rand()%sz;


// 	vector<int> left, right;
// 	for(int i = 0; i < (int)v.size(); i++) {
// 		if (piv == i) continue;
// 		if (ask(v[i], v[piv])) {
// 			left.push_back(v[i]);
// 		} else {
// 			right.push_back(v[i]);
// 		}
// 	}

// 	solve(left);
// 	res.push_back(v[piv]);
// 	solve(right);
// }

vector<int> solve(int l, int r) {
	vector<int> res;
	if (l == r) {
		res.push_back(l);
		return res;
	}

	int mid = (l + r) / 2;

	vector<int> a = solve(l, mid);
	vector<int> b = solve(mid + 1, r);

	if (ask(a.back(), b[0])) {
		for(int num : b) {
			a.push_back(num);
		}
		return a;
	} else {
		reverse(b.begin(), b.end());
		reverse(a.begin(), a.end());
		for(int num : a) {
			b.push_back(num);
		}
		return b;
	}
}

int main() {
	srand(time(NULL));

	vector<int> v;
	scanf("%d",&n);

	if (n == 1) {
		printf("0 1\n");
		return 0;
	}

	vector<int> zz = solve(1, n);
	printf("0 ");
	for(int i = 0; i < (int)zz.size(); i++) {
		if (i == (int)zz.size() - 1) printf("%d\n",zz[i]);
		else printf("%d ",zz[i]);
	}

	fflush(stdout);
	return 0;
}