#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define f first
#define s second
#define mp make_pair

const int N = 2e5 + 5;

struct point{
	int x, y, id;
};

point arr[N];

bool cmp(point a, point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

ll cross(point p, point q, point r) {
	return (p.x - q.x)*(r.y - q.y) - (p.y - q.y)*(r.x - q.x);
}

bool bol[N];

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n;
		scanf("%d",&n);
		for(int i = 1; i <= n; i++) {
			scanf("%d %d",&arr[i].x, &arr[i].y);
			arr[i].id = i;
		}
		
		sort(arr + 1, arr + n + 1, cmp);
		
		int last = 0;
		for(int i = 1; i < n; i++) {
			if (arr[i].x == arr[i+1].x) {
				last = i+1;
			} else {
				break;
			}
		}
		
		// printf("SAMPE %d\n",last);
		reverse(arr + 1, arr + last + 1);
		
		
		vector<point> low;
		vector<point> haha;
		
		for(int i = n; i >= 1; i--) {
			while(low.size() >= 2 && cross(low[low.size()-2], low[low.size()-1], arr[i]) < 0) {
				haha.pop_back();
				low.pop_back();
			}
			low.push_back(arr[i]);
			point a = arr[i];
			a.id = i;
			haha.push_back(a);
		}
		
		
		
		if ((int)low.size() == n) {
			for(int i = 0; i < n; i++) {
				if (i != n-1) printf("%d ", low[i].id-1);
				else printf("%d\n",low[i].id-1);
			}
		} else {
			memset(bol, false, sizeof bol);
			for(int i = 0; i < (int)low.size(); i++) {
				bol[haha[i].id] = true;
			}
			
			vector<point> ans;
			ans.push_back(arr[1]);
			
			for(int i = 1; i <= n; i++) {
				if (!bol[i]) {
					ans.push_back(arr[i]);
					//printf("ADA %d\n",i);
				}
			}
			
			for(int i = 0; i < (int)low.size()-1; i++) {
				ans.push_back(low[i]);
				//printf("%d\n",low[i].id);
				//printf("%d %d\n",low[i].x, low[i].y);
			}
			
			for(int i = 0; i < (int)ans.size(); i++) {
				if (i != (int)ans.size()-1) {
					printf("%d ",ans[i].id-1);
				} else {
					printf("%d\n",ans[i].id-1);
				}
			}
		}
	}
}