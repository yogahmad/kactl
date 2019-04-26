#include <bits/stdc++.h>
using namespace std;

#define LL long long

struct point {
	LL x, y; 
	point() { } ;
	point(LL _x, LL _y) {
	    x = _x, y = _y;
	}
};

LL cross(point p, point q, point r) {
	return((p.x - q.x)*(r.y - q.y) - (p.y - q.y)*(r.x - q.x));
}

//jangan lupa sort dulu buat convex
vector<point> makeconvex(vector<point> P) {
    vector<point> res; res.clear(); 
    int n = P.size();
	for(int i=0; i<n; i++) {
		while ((res.size()>=2)&&(cross(res[res.size()-2],res[res.size()-1],P[i])<=0)) res.pop_back();
		res.push_back(P[i]);
	}
	vector<point> tmpx;
	tmpx.clear();
	for(int i=n-1; i>=0; i--) {
		while ((tmpx.size()>=2)&&(cross(tmpx[tmpx.size()-2],tmpx[tmpx.size()-1],P[i])<=0)) tmpx.pop_back();
		tmpx.push_back(P[i]);
	}
	for(int i=1; i<tmpx.size(); i++) res.push_back(tmpx[i]);
	return res;
}

vector<point> v;

const double sq2 = sqrt(2);

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0,  0,-1};

double dist(point a, point b) {
    b.x -= a.x;
    b.y -= a.y;
    b.x = fabs(b.x);
    b.y = fabs(b.y);
    return (double)min(b.x, b.y) * sq2 + max(b.x, b.y) - min(b.x, b.y);
}

bool cmp(point a, point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

int main() {
    freopen("e.in", "r", stdin);
    
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d",&x, &y);
        for(int j = 0; j < 4; j++) 
            v.push_back(point(x + dx[j], y + dy[j]));
    }

    sort(v.begin(), v.end(), cmp);
    v = makeconvex(v);

    double ans = 0;
    int sz = v.size();
    for(int i = 0; i < sz; i++) {
        int nxt = (i + 1)%sz;
        ans += dist(v[i], v[nxt]);
    }

    printf("%.6lf\n",ans);
}