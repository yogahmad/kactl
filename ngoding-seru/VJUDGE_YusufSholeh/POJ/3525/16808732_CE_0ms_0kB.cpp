#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i < (b); i++) 
#define sz(x) ((int)x.size())
#define EPS 1e-9

typedef long double LD;

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
int lineIntersection(const P& s1, const P& e1, const P& s2, const P& e2, P& r) {
  if ((e1-s1).cross(e2-s2)) { // i f not parallell
    r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
    return 1;
  } else return -((e1-s1).cross(s2-s1)==0 || s2==e2);
}

typedef Point<LD> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
  vector<P> res;
  rep(i,0,sz(poly)) {
    P cur = poly[i], prev = i ? poly[i-1] : poly.back();
    bool side = s.cross(e, cur) > 0;
    if (side != (s.cross(e, prev) > 0)) {
      res.emplace_back();
      lineIntersection(s, e, cur, prev, res.back());
    }
    if (side) res.push_back(cur);
  }
  return res;
}

int n;

typedef Point<long double> point;
typedef Point<LD> P;
typedef vector<int> vi;

#define trav(x, y) for(auto &x : y)
#define all(x) x.begin(), x.end()

pair<vi, vi> ulHull(const vector<P>& S) {
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
vi convexHull(const vector<P>& S) {
  vi u, l; tie(u, l) = ulHull(S);
  if (sz(S) <= 1) return u;
  if (S[u[0]] == S[u[1]]) return {0};
  l.insert(l.end(), u.rbegin()+1, u.rend()-1);
  return l;
}

void makeconvex(vector<P>& gg) {
  vi cur = convexHull(gg);
  vector<P> zz;
  trav(i, cur) {
    zz.push_back(gg[i]);
  }
  gg = zz;
}

int main() {
  ios_base::sync_with_stdio(false);
  while(true) {
    cin >> n;
    if (n == 0) return 0;

    vector<point> p;

    for(int i = 0; i < n; i++) {
      int u, v;
      cin >> u >> v;
      p.push_back(point(u, v));
    }

    p.push_back(p[0]);

    LD l = 0, r = 2e4;
    for(int k = 0; k < 100; k++) {
      LD mid = (l + r) / 2.0;

      bool is_polygon = true;

      vector<point> tmp = p;
      tmp.pop_back();

      for(int i = 0; i < sz(p)-1; i++) {
        point from = p[i];
        point to = p[i+1];
        point vec = to - from;
        
        point s = (vec.perp() * mid) / vec.dist() + from;
        point e = (vec.perp() * mid) / vec.dist() + to;

        point news = (s - e) * 1e5 + e;
        point newe = (e - s) * 1e5 + s;

        tmp = polygonCut(tmp, news, newe);
        // makeconvex(tmp);

        if ((int)tmp.size() <= 2){
          is_polygon = false;
        } 
      }

      if (is_polygon) {
        l = mid;
      } else {
        r = mid;
      }
    }

    cout << fixed << setprecision(8) << (l + r) / 2.0 << "\n";
  }

  return 0;
}