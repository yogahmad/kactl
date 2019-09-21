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

bool found(ll x, ll y) {
  point RES; RES.y = -1e9;
  ll ly = -100, ry = y;
  while(ly <= ry) {
    ll midy = (ly + ry)/2;

    ll lx = -100, rx = x;

    ll anska = 2e9;
    while(lx <= rx) {
      ll midx = (lx + rx)/2;
      if (cross(FIRST, THIRD, mp(midx, midy)) > 0) {
        anska = midx;
        rx = midx - 1;
      } else {
        lx = midx + 1;
      }
    }

    lx = -100, rx = x;
    ll anski = -2e9;
    while(lx <= rx) {
      ll midx = (lx + rx)/2;
      if (cross(SECOND, THIRD, mp(midx, midy)) < 0) {
        anski = midx;
        lx = midx + 1;
      } else {
        rx = midx - 1;
      }
    }

    if (anski >= anska) {
      RES.x = anski;
      RES.y = midy;
      ly = midy + 1; 
    } else {
      ry = midy - 1;
    }
  }

  // cout << "AHAHAA\n";
  // cout << FIRST.x << " " << FIRST.y << endl;
  // cout << SECOND.x << " " << SECOND.y << endl;
  // cout << x << " " << y << endl;
  // cout << "END" << endl;

  // cin.ignore(); 
// 
  if (RES.y >= 0 && RES.y <= y) {
    long double A1 = area_t(FIRST, SECOND, THIRD);
    long double A2 = area_t(FIRST, SECOND, RES);
    A1 /= 2.0; A2 /= 2.0;
    // printf("MULAI %.5Lf %.5Lf %.5Lf\n",A1, A2, A1-A2);
    if (A1 - A2 < 25000) {
      CACAT = RES;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
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


    bool ganti = false;

    while(!found(x, y)) {
      FIRST.y += 1;
    }
    
    if (swapped) swap(FIRST.x, FIRST.y), swap(SECOND.x, SECOND.y), swap(THIRD.x, THIRD.y), swap(CACAT.x, CACAT.y);
    printf("4\n");
    printf("%lld %lld\n",FIRST.x, FIRST.y);
    printf("%lld %lld\n",THIRD.x, THIRD.y);
    printf("%lld %lld\n",SECOND.x, SECOND.y);
    printf("%lld %lld\n",CACAT.x, CACAT.y);
  }

  return 0;
}
