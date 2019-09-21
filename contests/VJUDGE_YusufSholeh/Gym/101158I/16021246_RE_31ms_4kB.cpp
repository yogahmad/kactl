#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> point;
#define x first
#define y second
#define mp make_pair

const ll INFY = 2e9;
const ll BATAS_AREA = 1e4;

point FIRST, SECOND, THIRD;
point CACAT;

ll cross(point p, point q, point r) {
  return (p.x - q.x)*(r.y - q.y) - (p.y - q.y)*(r.x - q.x);
}

ll area_t(point a, point b, point c) {
  return (b.x - a.x) * c.y;
}

long double area(vector<point> P) {
  long double result = 0.0;
  for(int i = 0; i < (int)P.size()-1; i++) {
    result += P[i].x * P[i+1].y - P[i+1].x * P[i].y;
  }
  return fabs(result) / 2.0;
}

bool found(ll x, ll y) {
  return false;
}

int main() {
  ll tc;
  scanf("%lld",&tc);
  // tc = 1e9;
  // srand(time(NULL));
  while(tc--) {
    ll x, y;
    scanf("%lld %lld",&x, &y);
    // x = rand();
    // y = rand();
    // const int MODD = 1e9;
    // x = (x * y) % MODD;
    // y = (y * x) % MODD;

    // cout << "WHAT " << endl;
    // cout << x << " " << y << endl;

    bool swapped = false;
    if (x < y) {
      swap(x, y);
      swapped = true;
    }

    FIRST = mp(0,0);
    SECOND = mp(1,0);
    THIRD = mp(x, y);

    if (area_t(FIRST, SECOND, THIRD) <= BATAS_AREA) {
      if (swapped) swap(FIRST.x, FIRST.y), swap(SECOND.x, SECOND.y), swap(THIRD.x, THIRD.y);
      printf("3\n");
      printf("%lld %lld\n",FIRST.x, FIRST.y);
      printf("%lld %lld\n",SECOND.x, SECOND.y);
      printf("%lld %lld\n",THIRD.x, THIRD.y);
      continue;
    }

    ll gc = __gcd(x, y);

    FIRST = mp(0, 1);
    THIRD = mp(x, y);
    SECOND = mp(1, 0);
    CACAT = mp(x - x/gc, y - y/gc);

    bool sdh = false;

    vector<point> PP;
    PP.push_back(FIRST); 
    PP.push_back(THIRD); 
    PP.push_back(SECOND); 
    PP.push_back(CACAT);
    PP.push_back(FIRST);
    if (area(PP) < 25000) {
      sdh = true;
    }
    
    if (!sdh) for(ll j = y-1; j >= y-10000; j--) {
      if (j == 0) {
        assert(0);
      }

      FIRST = mp(0, 0);

      ll ka = j;
      ll lx = 1, rx = x;
      while(lx <= rx) {
        ll midx = (lx + rx)/2;
        if (cross(FIRST, THIRD, mp(midx, j)) > 0) {
          ka = midx;
          rx = midx - 1;
        } else {
          lx = midx + 1;
        }
      }

      point NEW_TOP = mp(ka, j);

      ll minx = x;
      lx = 1, rx = x;
      while(lx <= rx) {
        ll midx = (lx + rx)/2;
        if (cross(THIRD, mp(midx, 0), NEW_TOP) > 0) {
          minx = midx;
          rx = midx - 1;
        } else {
          lx = midx + 1;
        }
      }

      vector<point> P;
      P.push_back(FIRST), P.push_back(THIRD), P.push_back(mp(minx, 0)), P.push_back(NEW_TOP), P.push_back(FIRST);

      if (area(P) < 25000) {
        // printf("DAPAT\n");
        SECOND = mp(minx, 0);
        CACAT = NEW_TOP;
        break;
      }
    }
    
    if (swapped) swap(FIRST.x, FIRST.y), swap(SECOND.x, SECOND.y), swap(THIRD.x, THIRD.y), swap(CACAT.x, CACAT.y);
    printf("4\n");
    printf("%lld %lld\n",FIRST.x, FIRST.y);
    printf("%lld %lld\n",THIRD.x, THIRD.y);
    printf("%lld %lld\n",SECOND.x, SECOND.y);
    printf("%lld %lld\n",CACAT.x, CACAT.y);

    if (swapped) swap(FIRST.x, FIRST.y), swap(SECOND.x, SECOND.y), swap(THIRD.x, THIRD.y), swap(CACAT.x, CACAT.y);
    // cout << cross(FIRST, THIRD, CACAT) << endl; 
    // cout << cross(SECOND, THIRD, CACAT) << endl; 
    assert(cross(SECOND, THIRD, CACAT) < 0);
    assert(cross(FIRST, THIRD, CACAT) > 0);
    assert(0 <= FIRST.x && FIRST.x <= x);
    assert(0 <= FIRST.y && FIRST.y <= y);
    assert(0 <= SECOND.x && SECOND.x <= x);
    assert(0 <= SECOND.y && SECOND.y <= y);
    assert(0 <= THIRD.x && THIRD.x <= x);
    assert(0 <= THIRD.y && THIRD.y <= y);
    assert(0 <= CACAT.x && CACAT.x <= x);
    assert(0 <= CACAT.y && CACAT.y <= y);
  }

  return 0;
}
