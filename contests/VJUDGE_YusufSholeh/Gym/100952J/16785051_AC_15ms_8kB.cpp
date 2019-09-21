#include <bits/stdc++.h>
using namespace std;

#define INF 1e20
#define EPS 1e-9
#define PI acos(-1.0)

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { int id; double x, y;   // only used if more precision is needed
  point() { id = x = y = 0.0; }                      // default constructor
  point(double _x, double _y) : id(0), x(_x), y(_y) {}        // user-defined
  point(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}
  bool operator == (point other) const {
   return (fabs(x - other.x) < EPS && other.id == id && (fabs(y - other.y) < EPS)); }
  bool operator < (point other) const {
    return (fabs(x - other.x) < EPS ? y < other.y : x < other.x); }};


void printPoint(point a) {
    printf("id: %d (%.2lf, %.2lf)\n", a.id, a.x, a.y);
}

struct vec { double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y); }

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double

  // returns the area, which is half the determinant
double area(const vector<point> &P) {
  double result = 0.0, x1, y1, x2, y2;
  for (int i = 0; i < (int)P.size()-1; i++) {
    x1 = P[i].x; x2 = P[i+1].x;
    y1 = P[i].y; y2 = P[i+1].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2.0; }

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }


bool isInside(point a, point p, point q) {
    return fabs(dist(a, p) + dist(a, q) - dist(p, q)) < EPS;
}

double det(double a,double b,double c,double d) {
    return(a * d - b * c);
}

// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
  if ((int)P.size() == 0) return false;
  double sum = 0;    // assume the first vertex is equal to the last vertex
  for (int i = 0; i < (int)P.size()-1; i++) {
    if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
    else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
  return fabs(fabs(sum) - 2*PI) < EPS; }

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  if (fabs(u + v) < EPS) return point(-INF, -INF);
  return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }

point pivot;
bool angleCmp(point a, point b) {                 // angle-sorting function
  if (collinear(pivot, a, b))                               // special case
    return dist(pivot, a) < dist(pivot, b);    // check which one is closer
  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; }   // compare two angles

vector<point> CH(vector<point> P) {   // the content of P may be reshuffled
  int i, j, n = (int)P.size();
  if (n <= 3) {
    if (!(P[0] == P[n-1])) P.push_back(P[0]); // safeguard from corner case
    return P;                           // special case, the CH is P itself
  }

  // first, find P0 = point with lowest Y and if tie: rightmost X
  int P0 = 0;
  for (i = 1; i < n; i++)
    if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;

  point temp = P[0]; P[0] = P[P0]; P[P0] = temp;    // swap P[P0] with P[0]

  // second, sort points by angle w.r.t. pivot P0
  pivot = P[0];                    // use this global variable as reference
  sort(++P.begin(), P.end(), angleCmp);              // we do not sort P[0]

  // third, the ccw tests
  vector<point> S;
  S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);   // initial S
  i = 2;                                         // then, we check the rest
  while (i < n) {           // note: N must be >= 3 for this method to work
    j = (int)S.size()-1;
    if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);  // left turn, accept
    else S.pop_back(); }   // or pop the top of S until we have a left turn
  return S; }                                          // return the result

vector<point> arr, brr, total, gabung, inters;
double area_a, area_b, area_gabung;
int n, m;

void getInters() {
    // printf("%d\n", inters.find(point(3, 0, 2)) == inters.end());
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < brr.size(); j++) {
            point inter = lineIntersectSeg(arr[i], arr[(i + 1) % arr.size()], brr[j], brr[(j + 1) % brr.size()]);
            if (!(inter == point(-INF, -INF)) && isInside(inter, arr[i], arr[(i + 1) % arr.size()]) && isInside(inter, brr[j], brr[(j + 1) % brr.size()])) {
                inter.id = 3;
                inters.push_back(inter);
            }
        }
    }
}

int findIdx(vector<point> v, point p) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == p)
            return i;
    }
    return -1;
}



vector<point> sortCcw(vector<point> v) {
	sort(v.begin(), v.end());

  pivot = v[0];
  int len = v.size();
  sort(++v.begin(), v.end(), angleCmp);
  int atas = len - 1;

  while (collinear(v[0], v[len - 1], v[atas])) {
    atas--;
  }

  reverse(v.begin() + atas + 1, v.end());
  return v;
}

int main() {
    // vector<point> v;
    // v.push_back(point(0, 0));
    // v.push_back(point(3, 0));
    // v.push_back(point(3, 1));
    // v.push_back(point(0, 3));
    // v.push_back(point(0, 2));
    // v.push_back(point(-1, 2));
    // v.push_back(point(-0.5, 1.0));

    // v = sortCcw(v);
    // for (int i = 0; i < v.size(); i++) {
    //   printPoint(v[i]);
    // }
    // point hehe = lineIntersectSeg(point(0, 0), point(2, 0), point(-1, 1), point(4, 1));
    // printPoint(hehe);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        inters.clear();
        arr.clear();  brr.clear();
        gabung.clear();  total.clear();

        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            arr.push_back(point(1, x, y));
            total.push_back(point(1, x, y));
        }

        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            brr.push_back(point(2, x, y));
            total.push_back(point(2, x, y));
        }

        getInters();
        total = CH(total);
        arr = CH(arr);
        area_a = area(arr);
        brr = CH(brr);
        area_b = area(brr);


        if (inters.size() == 0) {
          if (inPolygon(arr[0], brr))
            printf("%.4lf\n", area_a);
          else if (inPolygon(brr[0], arr)) {
            printf("%.4lf\n", area_b);
          } else {
            printf("%.4lf\n", 0.0);
          }
          continue;
        }

        for (int i = 0; i < inters.size(); i++) {
          arr.push_back(inters[i]);
          brr.push_back(inters[i]);
				}

        arr = sortCcw(arr);
        brr = sortCcw(brr);

        // printf("--------------arr-------------\n");
        // for (int i = 0; i < arr.size(); i++) {
        //     printPoint(arr[i]);
        // }
        // printf("--------------brr-------------\n");
        // for (int i = 0; i < brr.size(); i++) {
        //     printPoint(brr[i]);
        // }
        // printf("--------------total-------------\n");
        // for (int i = 0; i < total.size(); i++) {
        //     printPoint(total[i]);
        // }
        // printf("\n");
        gabung.push_back(total[0]);
        for (int i = 1; i < total.size(); i++) {
            // printf("->  ");
            // printPoint(total[i]);
            if (total[i].id != total[i-1].id) {
                if (total[i].id == 2) {
                    int p = (findIdx(arr, total[i-1]) + 1) % arr.size();
                    while (arr[p].id != 3) {
                        gabung.push_back(arr[p]);
                        p = (p + 1) % arr.size();
                    }
                    gabung.push_back(arr[p]);
                    // printf("arr[p]: ");
                    // printPoint(arr[p]);
                    int q = (findIdx(brr, arr[p]) + 1) % brr.size();
                    // printf("q: %d\n", q);
                    // printf("q: %d\n", q);
                    // printf("brr[q]: ");
                    // printPoint(brr[q]);
                    // printf("sini\n");
                    // printPoint(brr[q]);
                    while (!(brr[q] == total[i])) {
                        gabung.push_back(brr[q]);
                        q = (q + 1) % brr.size();
                    }
                } else if (total[i].id == 1) {
                  int q = (findIdx(brr, total[i-1]) + 1) % brr.size();
                  while (brr[q].id != 3) {
                    gabung.push_back(brr[q]);
                    q = (q + 1) % brr.size();
                  }
                  gabung.push_back(brr[q]);
                  int p = (findIdx(arr, brr[q]) + 1) % arr.size();
                  while (!(arr[p] == total[i])) {
                    gabung.push_back(arr[p]);
                    p = (p + 1) % arr.size();
                  }
                }
            }
            gabung.push_back(total[i]);
        }
        area_gabung = area(gabung);

        // printf("----------gabung----------\n");
        // for (int i = 0; i < gabung.size(); i++) {
        //     printPoint(gabung[i]);
        // }
        // cout << area_a + area_b - area_gabung << endl;
        // printf("%.4lf %.4lf %.4lf\n", area_a, area_b, area_gabung);
        // if (fabs(area_a + area_b - area_gabung + 284594) < EPS) {
            // ini cuma mau nyoba ngetest tc yang lain salahnya apa
            // printf("%.4lf\n", 4623.9427);
        // }
        // else {
          printf("%.4lf\n", area_a + area_b - area_gabung);
        // }
    }
}
