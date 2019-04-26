#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;

#define sz(x) ((int)x.size())
const LD EPS = 1e-9;


template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	LD dist() const { return sqrt((LD)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	LD angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(LD a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

template<class P>
int segmentIntersection(const P& s1, const P& e1,
		const P& s2, const P& e2, P& r1, P& r2) {
	if (e1==s1) {
		if (e2==s2) {
			if (e1==e2) { r1 = e1; return 1; } //all equal
			else return 0; //different point segments
		} else return segmentIntersection(s2,e2,s1,e1,r1,r2);//swap
	}
	//segment directions and separation
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = v1.cross(d), a2 = v2.cross(d);
	if (a == 0) { //if parallel
		auto b1=s1.dot(v1), c1=e1.dot(v1),
		     b2=s2.dot(v1), c2=e2.dot(v1);
		if (a1 || a2 || max(b1,min(b2,c2))>min(c1,max(b2,c2)))
			return 0;
		r1 = min(b2,c2)<b1 ? s1 : (b2<c2 ? s2 : e2);
		r2 = max(b2,c2)>c1 ? e1 : (b2>c2 ? s2 : e2);
		return 2-(r1==r2);
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	if (0<a1 || a<-a1 || 0<a2 || a<-a2)
		return 0;
	r1 = s1-v1*(a2/a);
	return 1;
}

typedef Point<long double> point;

template<class P>
LD segDist(const P& a, const P& b, const P& p, P& c) {
  LD u = (p-a).dot(b-a) / (b-a).dist2();
	if (u < 0.0) {
		c = a;
		return (p - a).dist();
	} else if (u > 1.0) {
		c = b;
		return (p - b).dist();
	}
  c = a + ((b - a) * u);
  return (c - p).dist();
}

int n;

bool on_left(point p, point q, point r) { // r is on the left of p..q
	return q.cross(r, p) > -0.5;
}

LD majagad[305][305];

int main() {
	vector<point> v;

	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		v.push_back(point(x,y));
	}

	vector<point> poly = v;
	poly.push_back(poly[0]);

	LD ans = 0;

	for(int i = 0; i < sz(v); i++) {
		for(int j = 0; j < sz(v); j++) if (i != j) {
 
			LD jar = (v[j] - v[i]).dist();
			point L = v[i];

			ll l = 0, r = 1e8;
			for(int k = 0; k < 100; k++) {
				LD mid = (l + r)/2.0;
				point cur = (v[j] - v[i]) * mid + v[i];

				if (fabs(cur.x) >= 5e6 && fabs(cur.y) >= 5e6) {
					r = mid;
				} else {
					l = mid;
				}
			}
			point R = (v[j] - v[i]) * l + v[i];

			// printf("%.5Lf %.5Lf\n",R.x, R.y);

			vector<point> nyentuh;
			vector<point> ujung;

			int siz = sz(poly);
			for(int k = 0; k < siz-1; k++) {
				point r1, r2;
				int result = segmentIntersection(L, R, poly[k], poly[k+1], r1, r2);

				if (result == 1) {
					if ((r1 - v[i]).dist() < EPS || (r1 - v[j]).dist() < EPS || (r1 - poly[k]).dist() < EPS || (r1 - poly[k+1]).dist() < EPS) {
						nyentuh.push_back(r1);
					} else {
						ujung.push_back(r1);
					}
				} else if (result == 2) {
					nyentuh.push_back(r1);
					nyentuh.push_back(r2);
				}
			}

			LD gg = 1e18;
			for(point ada : ujung) {
				gg = min(gg, (ada - L).dist());
			}
			
			vector<int> sentuh;

			for(int k = 0; k < sz(v); k++) {
				point dumb = point(0,0);
				if (segDist(v[i], R, v[k], dumb) < EPS) {
					sentuh.push_back(k);
				}
			}
			
			for(int idx : sentuh) {
				point prv = (idx == 0) ? v.back() : v[idx-1];
				point nxt = (idx == sz(v) - 1) ? v[0] : v[idx+1];
				point cur = v[idx];

				// if(i==3 && j==5) printf("%d %d %.5Lf %.5Lf\n",i,j,cur.x, cur.y);
				
				bool sudut = on_left(prv, cur, nxt);
				if (sudut) {
					// if(i==3 && j==5) printf("masuk1\n");
					if (on_left(prv, cur, R) && on_left(cur, nxt, R)) {
						// if(i==3 && j==5) printf("hehe\n");
					} else {
						gg = min(gg, (cur - L).dist());
					}
				} else {
					// if(i==3 && j==5) printf("masuk2\n");
					if (on_left(prv, cur, R) || on_left(cur, nxt, R)) {
						// if(i==3 && j==5) printf("hehe\n");
					} else {
						gg = min(gg, (cur - L).dist());
					}
				}
				// check if prv -> cur -> nxt mengapit prv -> cur -> R;
			}
			assert(gg != 1e18);
			majagad[i][j] = gg;
		}
	}

	for(int i = 0; i < sz(v); i++) {
		for(int j = 0; j < sz(v); j++) if (i != j) {
			LD jar = (v[i] - v[j]).dist();
			ans = max(ans, majagad[i][j]);
			if (majagad[i][j] > jar && majagad[j][i] > jar) {
				ans = max(ans, majagad[i][j] + majagad[j][i] - jar);
			}
		}
	}

	cout << fixed << setprecision(8) << ans << endl;

  return 0;
}
