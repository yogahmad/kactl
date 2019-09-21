#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()
#define trav(a, x) for (auto& a : x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define f first
#define s second
#define mp make_pair

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
	// angle to x−axis in interval [−pi , pi ]
	LD angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist ()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated ’a ’ radians ccw around the origin
	P rotate(LD a) const {
	return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

template<class P>
int segmentIntersection(const P& s1, const P& e1,
	const P& s2, const P& e2, P& r1, P& r2) {
	if (e1==s1) {
		if (e2==s2) {
		if (e1==e2) { r1 = e1; return 1; } // a l l equal
		else return 0; //different point segments
		} else return segmentIntersection(s2,e2,s1,e1,r1,r2);//swap
	}
	//segment directions and separation
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = v1.cross(d), a2 = v2.cross(d);
	if (a == 0) { // i f parallel
		auto b1=s1.dot(v1), c1=e1.dot(v1),
		b2=s2.dot(v1), c2=e2.dot(v1);
		if (a1 || a2 || max(b1,min(b2,c2))>min(c1,max(b2,c2))) return 0;
		r1 = min(b2,c2)<b1 ? s1 : (b2<c2 ? s2 : e2);
		r2 = max(b2,c2)>c1 ? e1 : (b2>c2 ? s2 : e2);
		return 2-(r1==r2);
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	if (0<a1 || a<-a1 || 0<a2 || a<-a2)
		return 0;
	r1 = s1-v1*a2/a;
	return 1;
}

int n, m;

typedef Point<LD> point;
typedef vector<int> vi;

pair<vi, vi> ulHull(const vector<point>& S) {
	vi Q(sz(S)), U, L;
	iota(all(Q), 0);
	sort(all(Q), [&S](int a, int b){ return S[a] < S[b]; });
	trav(it, Q) {
		#define ADDP(C, cmp) while (sz(C) > 1 && S[C[sz(C)-2]].cross(\
		S[it], S[C.back()]) cmp 0) C.pop_back(); C.push_back(it);
		ADDP(U, <=); ADDP(L, >=);
	}
	return {U, L};
}

vi convexHull(const vector<point>& S) {
	vi u, l; tie(u, l) = ulHull(S);
	if (sz(S) <= 1) return u;
	if (S[u[0]] == S[u[1]]) return {0};
	l.insert(l.end(), u.rbegin()+1, u.rend()-1);
	return l;
}

LD polygonArea2(vector<point>& v) {
	LD a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

template<class P>
int sideOf(const P& s, const P& e, const P& p) {
	auto a = (e-s).cross(p-s);
	return (a > 0) - (a < 0);
}

bool inside(point a, vector<point> &S) {
	for(int i = 0; i < sz(S)-1; i++) {
		bool left = sideOf(S[i], S[i+1], a)>=0;
		if (!left) return false;
	}
	return true;
}

int main() {
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		scanf("%d %d",&n, &m);

		vector<point> p1, p2;
		for(int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d %d",&x, &y);
			p1.push_back(point(x,y));
		}
		for(int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d %d",&x, &y);
			p2.push_back(point(x, y));
		}

		vector<point> hull1, hull2;
		vi id1 = convexHull(p1), id2 = convexHull(p2);
		trav(i, id1) {
			hull1.push_back(p1[i]);
		} 
		trav(i, id2) {
			hull2.push_back(p2[i]);
		}

		hull1.push_back(hull1[0]);
		hull2.push_back(hull2[0]);

		vector<point> intersect;
		for(int i = 0; i < sz(hull1)-1; i++) {
			for(int j = 0; j < sz(hull2)-1; j++) {
				point r1, r2;
				int res = segmentIntersection(hull1[i], hull1[i+1], hull2[j], hull2[j+1], r1, r2);
				assert(res != 2);
				if (res == 1) {
					// cout << " ================ " << endl;
					// cout << hull1[i].x << "  " << hull1[i].y << "  " << hull1[i+1].x << " " << hull1[i+1].y << endl;
					// cout << hull2[j].x << "  " << hull2[j].y << "  " << hull2[j+1].x << " " << hull2[j+1].y << endl;
					// cout << r1.x << " Y " << r1.y << endl;
					intersect.push_back(r1);
				}
			}
		}	

		for(int i=0; i < sz(hull1)-1; i++) {
			if (inside(hull1[i], hull2)) {
				intersect.push_back(hull1[i]);	
			}
		}
		for(int i = 0; i < sz(hull2)-1; i++) {
			if (inside(hull2[i], hull1)) {
				intersect.push_back(hull2[i]);
			}
		}

		if (sz(intersect) > 2) {
			vi id3 = convexHull(intersect);
			vector<point> hull3;
			trav(i, id3) {
				hull3.push_back(intersect[i]);
			}
			cout << fixed << setprecision(4) << polygonArea2(hull3)/2.0 << endl;
		} else {
			printf("0.0000\n");
		}

		
	}
	return 0;
}