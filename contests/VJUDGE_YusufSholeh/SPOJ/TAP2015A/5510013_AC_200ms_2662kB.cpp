#include<cmath>
#include<iostream>
#define EPS 1e-9
using namespace std;
struct point {
	double x, y, r; 
	point() { } ;
	point(double _x, double _y, double _r) {
		x = _x, y = _y; r = _r;
	}
} P[105];
double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}
int n, ans(1);
int go(point C) {
	int res = 0;
	for(int i = 1; i <= n; i++)
		if (dist(P[i], C) <= P[i].r + EPS)
			res++;
	return res;
}
int main() {
	while(scanf("%d",&n) != EOF) {
		ans = 1;
		for(int i = 1; i <= n; i++) {
			double x,y,r;
			scanf("%lf %lf %lf",&x,&y,&r);
			P[i] = point(x,y,r);
		}
		for(int i = 1; i < n; i++) {
			for(int j = i + 1; j <= n; j++) {
				double d = dist(P[i], P[j]);
				double r0 = P[i].r, x0 = P[i].x, y0 = P[i].y;
				double r1 = P[j].r, x1 = P[j].x, y1 = P[j].y;
				point center;
				if (d > r0 + r1) continue;
				if (d < fabs(r0 - r1) || fabs(d) < EPS) {
					if (r0 < r1) center = P[i];
					else center = P[j];
				} else {
					double a = (r0*r0 - r1*r1 + d*d)/(2*d);
					double h = sqrt(r0*r0 - a*a);
					
					double x2 = x0 + a*(x1 - x0)/d;
					double y2 = y0 + a*(y1 - y0)/d;
					
					double translationY = h*(y1 - y0)/d;
					double translationX = h*(x1 - x0)/d;
					
					center.x = x2 + translationY;
					center.y = y2 - translationX;
					ans = max(ans, go(center));
					center.x = x2 - translationY;
					center.y = y2 + translationX;
				}
				ans = max(ans, go(center));
			}
		}
		printf("%d\n",ans);
	}
}