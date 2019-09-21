#include<bits/stdc++.h>
using namespace std;
#define MAX 1005
int n;

vector<int> v[MAX];
int vis[MAX];
int with[MAX];
int flag[MAX];
int day = 0;

bool match(int x) {
	int size = v[x].size();
	for(int i = 0; i < size; i++) {
		int next = v[x][i];
		if (vis[next] != day) {
			vis[next] = day;
			if (with[next] == -1 || match(with[next])) {
				with[next] = x;
				return true;
			}
		}
	}
	return false;
}

struct student{
	int height;
	string sex;
	string music;
	string sport;
};

student arr[MAX];

int condition(student a, student b) {
	int ret = 0;
	if (abs(a.height - b.height) > 40) ret++;
	if (a.sex == b.sex) ret++;
	if (a.music != b.music) ret++;
	if (a.sport == b.sport) ret++;
	return ret;
}

int main() {
	int tc; scanf("%d",&tc);
	while(tc--) {
		scanf("%d",&n);
		for(int i = 1; i <= n; i++) {
			cin >> arr[i].height >> arr[i].sex >> arr[i].music >> arr[i].sport;
		}
		
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if (i == j) continue;
				if (arr[i].sex == "M" && condition(arr[i], arr[j]) == 0) {
					v[i].push_back(j);					
				}
			}
		}
		
		int ans = 0;
		memset(with,-1,sizeof(with));
		for(int i = 1; i <= n; i++) {
			day++;
			if (match(i)) ans++;
		}
		
		
		for(int i = 1; i <= n; i++) v[i].clear();
		printf("%d\n",n-ans);
	}
}