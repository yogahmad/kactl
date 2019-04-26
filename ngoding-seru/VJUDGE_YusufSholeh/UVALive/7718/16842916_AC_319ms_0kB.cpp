#include <bits/stdc++.h>
using namespace std;

#define sz(x) ((int)x.size())
#define rep(i,a,b) for(int i = a; i < (b); i++)
#define trav(i, x) for(auto &i : x)

typedef long double LD;
typedef long long ll;
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
	// angle to x-axis in interval [-pi, pi]
	LD angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(LD a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<LD> P;

LD lineDist(const P& a, const P& b, const P& p, P& c) {
  LD u = (p-a).dot(b-a) / (b-a).dist2();
  c = a + ((b - a) * u);
  return (c - p).dist();
}

LD segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max((LD).0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

bool circleIntersection(P a, P b, LD r1, LD r2,
		pair<P, P>& out) {
	P delta = b - a;
	assert(delta.x || delta.y || r1 != r2);
	if (!delta.x && !delta.y) return false;
	LD r = r1 + r2, d2 = delta.dist2();
	LD p = (d2 + r1*r1 - r2*r2) / (2.0 * d2);
	LD h2 = r1*r1 - p*p*d2;
	if (d2 > r*r || h2 < 0) return false;
	P mid = a + delta*p, per = delta.perp() * sqrt(h2 / d2);
	out = make_pair(mid + per, mid - per);
	return true;
}

typedef Point<LD> point;
typedef pair<point,point> line;

int x1, q1, x2, y2;
int n;
const LD EPS = 1e-10;
vector<point> poly;

bool insideRectangle(point cur) {
  return ((LD)x1 < cur.x + EPS && cur.x < (LD)x2 + EPS && 
    (LD)q1 < cur.y + EPS && cur.y < (LD)y2 + EPS);
}

int main() {
  int tc;
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  for(int cs = 1; cs <= tc; cs++) {
    cin >> x1 >> q1 >> x2 >> y2 >> n;
    
    poly.clear();
    line li[4];
    li[0] = mp(point(x1, q1), point(x2, q1));
    li[1] = mp(point(x2, q1), point(x2, y2));
    li[2] = mp(point(x2, y2), point(x1, y2));
    li[3] = mp(point(x1, y2), point(x1, q1));
    poly.push_back(point(x1, q1));
    poly.push_back(point(x2, q1));
    poly.push_back(point(x2, y2));
    poly.push_back(point(x1, y2));

    vector<point> v;
    for(int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      v.push_back(point(x,y));
    }

    ll l = 0, r = 1e16;
    ll ans = 0;

    while(l <= r) {
      ll mmid = (l + r) / 2;
      LD mid = mmid;

      // printf("PROCESS %lld\n", mmid);

      bool covered = false;
      // case where all point is inside a circle
      for(point cur : v) {
        int cnt = 0;
        for(point rect : poly) {
          if ((rect - cur).dist() + EPS < mid) {
            ++cnt;
          }
        }
        if (cnt == 4) {
          covered = true;
          break;
        }
      }

      if (covered) {
        ans = mmid;
        r = mmid - 1;
        continue;
      }

      vector<tuple<int,int,point>> intersect;

      bool touch_segment = false;

      for(int i = 0; i < sz(v); i++) {
        touch_segment = true;
        for(int j = i+1; j < sz(v); j++) {
          // circle-circle
          pair<point, point> isec;
          if (circleIntersection(v[i], v[j], mid, mid, isec)) {
            if (insideRectangle(isec.first)) {
              intersect.push_back(tie(i, j, isec.first));
            }
            if (insideRectangle(isec.second)) {
              intersect.push_back(tie(i, j, isec.second));
            }
          }
        }

        // circle - segment
        for(int j = 0; j < 4; j++) {
          if (segDist(li[j].first, li[j].second, v[i]) + EPS < mid) {
            point res;
            LD dist = lineDist(li[j].first, li[j].second, v[i], res);

            point first, second;
            LD linedist = (li[j].first - li[j].second).dist();

            if (dist < EPS) {
              LD d1 = (li[j].first - v[i]).dist();
              LD d2 = (li[j].second - v[i]).dist();
              first = (d1 < EPS) ? (li[j].second - li[j].first) * (mid / linedist) + v[i] : (li[j].first - v[i]) * (mid / d1) + v[i];
              second = (d2 < EPS) ? (li[j].first - li[j].second) * (mid / linedist) + v[i] : (li[j].second - v[i]) * (mid / d2) + v[i];
            } else {
              first = (v[i] - res).perp();
              second = (((v[i] - res).perp()).perp()).perp();
              first = first * (mid / dist) + res;
              second = second * (mid / dist) + res;
            }

            if (insideRectangle(first)) {
              touch_segment = true;
              intersect.push_back(make_tuple(i, i, first));
            } 
            if (insideRectangle(second)) {
              touch_segment = true;
              intersect.push_back(make_tuple(i, i, second));
            }
          }
        }
      }

      for(auto cur : poly) {
        intersect.push_back(make_tuple(-1, -1, cur));
      }

      if (sz(intersect) == 0 || touch_segment == false) {
          covered = false;
      } else {
        covered = true;
        for(auto cur : intersect) {
          
          int id1 = get<0>(cur);
          int id2 = get<1>(cur);
          point check = get<2>(cur); 

          bool exist = false;
          for(int i = 0; i < sz(v); i++) {
            if (i != id1 && i != id2) {
              if ((v[i] - check).dist() + EPS < mid) {
                exist = true;
                break;
              }
            }
          }

          if (!exist) {
            covered = false;
            break;
          }
        }
      }

      if (covered) {
        ans = mmid;
        r = mmid - 1;
      } else {
        l = mmid + 1;
      }
    }

    cout << "Case #" << cs << ": " << ans << endl;
  } 
  return 0;
}
