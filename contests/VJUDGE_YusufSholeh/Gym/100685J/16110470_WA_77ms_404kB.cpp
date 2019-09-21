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

vector<int> res;

void solve(vector<int> v) {
	int sz = v.size();
	if (v.size() == 1) {
		res.push_back(v[0]);
		return;
	} else if (v.size() == 0) {
		return;
	}

	
	int piv = rand()%sz;


	vector<int> left, right;
	for(int i = 0; i < (int)v.size(); i++) {
		if (piv == i) continue;
		if (ask(v[i], v[piv])) {
			left.push_back(v[i]);
		} else {
			right.push_back(v[i]);
		}
	}

	solve(left);
	res.push_back(v[piv]);
	solve(right);
}

int main() {
	srand(time(NULL));

	vector<int> v;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) v.push_back(i);

	solve(v);
	
	printf("0 "); 
	for(int i = 0; i < (int)res.size(); i++) {
		if (i == (int)res.size() - 1) printf("%d\n",res[i]);
		else printf("%d ",res[i]);
	}
	fflush(stdout);
	return 0;
}