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

ll extended_euclid(ll a, ll b, ll & x, ll & y) {
  if (a == 0) { x = 0; y = 1; return b; }
  ll x1, y1;
  ll d = extended_euclid(b%a, a, x1, y1);
  x = y1 - (b / a) * x1; y = x1;
  return d;
} 

int main() {
  ll tc;
  scanf("%lld",&tc);
  while(tc--) {
    ll x, y;
    scanf("%lld %lld",&x, &y);

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
    if (area(PP) <= 25000) {
      sdh = true;
    }

    if (!sdh) {
      FIRST = mp(0, 0);
      SECOND = mp(x, y);
      
      ll x0, y0;
      ll d = extended_euclid(x/gc, -y/gc, x0, y0);
      // printf("WHAT %lld %lld %lld\n",x0, y0, x0 * (x/gc) - y0 * (y/gc));
      // printf("%lld %lld\n",x/gc, y/gc);
      x0 *= 3, y0 *= 3;
      ll res = x0 * (x/gc) - y0 * (y/gc);
      x0 = x0 % (y/gc);
      y0 = ((x0 * x/gc) - res) / (y/gc);

      THIRD = mp(y0, x0);
      // printf("WHAT %lld %lld %lld\n",x0, y0, x0 * (x/gc) - y0 * (y/gc));

      if (swapped) swap(FIRST.x, FIRST.y), swap(SECOND.x, SECOND.y), swap(THIRD.x, THIRD.y), swap(CACAT.x, CACAT.y);
      printf("3\n");      
      printf("%lld %lld\n",FIRST.x, FIRST.y);
      printf("%lld %lld\n",THIRD.x, THIRD.y);
      printf("%lld %lld\n",SECOND.x, SECOND.y);

      if (swapped) swap(FIRST.x, FIRST.y), swap(SECOND.x, SECOND.y), swap(THIRD.x, THIRD.y), swap(CACAT.x, CACAT.y);
      PP.clear();
      PP.push_back(FIRST); 
      PP.push_back(THIRD); 
      PP.push_back(SECOND);
      PP.push_back(FIRST);  
      assert(area(PP) <= 25000);
      // assert(THIRD.first >= 0 && THIRD.first <= x);
      // assert(THIRD.second >= 0 && THIRD.second <= y);
      continue;
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
    // assert(cross(SECOND, THIRD, CACAT) < 0);
    // assert(cross(FIRST, THIRD, CACAT) > 0);
    // assert(0 <= FIRST.x && FIRST.x <= x);
    // assert(0 <= FIRST.y && FIRST.y <= y);
    // assert(0 <= SECOND.x && SECOND.x <= x);
    // assert(0 <= SECOND.y && SECOND.y <= y);
    // assert(0 <= THIRD.x && THIRD.x <= x);
    // assert(0 <= THIRD.y && THIRD.y <= y);
    // assert(0 <= CACAT.x && CACAT.x <= x);
    // assert(0 <= CACAT.y && CACAT.y <= y);
  }

  return 0;
}
