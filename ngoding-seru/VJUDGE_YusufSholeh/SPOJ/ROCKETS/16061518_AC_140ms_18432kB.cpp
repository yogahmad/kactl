#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point{
  int x, y, id;
  bool jenis;
  point() {}
  point(int _x, int _y, int _id, bool _jenis) {
    x = _x, y = _y, id = _id, jenis = _jenis;
  }
};

const point origin = point(0, 0, 0, 0);

typedef pair<int,int> pii;

const int N = 2e4 + 5;

int n;
int tc;
int match[N];

ll cross(point p, point q, point r) {
  return 1ll * (p.x - q.x) * (r.y - q.y) - 1ll * (p.y - q.y) * (r.x - q.x);
}

ll cross2(point p, point r) {
  return 1ll * p.x * r.y - 1ll * p.y * r.x;
}

bool cmp(point a, point b) {
  return cross2(a, b) > 0;
}

int solve2(vector<point> all, int picked, int sz) {
  point pick = all[picked];
  all.erase(all.begin() + picked);

  vector<point> up, low;
  for(point p : all) {
    p.x -= pick.x;
    p.y -= pick.y;
    if (p.y >= 0) up.push_back(p);
    else low.push_back(p);
  }

  sort(up.begin(), up.end(), cmp);
  sort(low.begin(), low.end(), cmp);

  // printf("point picked %d %d %d %d\n", pick.x, pick.y, pick.jenis, pick.id);
  // for(point p : all) {
  //   printf("%d %d %d %d\n",p.x, p.y, p.jenis, p.id);
  // }
  // printf("point at top\n");
  // for(point p : up) {
  //   printf("%d %d %d %d\n",p.x, p.y, p.jenis, p.id);
  // }
  // printf("point at bot\n");
  // for(point p : low) {
  //   printf("%d %d %d %d\n",p.x, p.y, p.jenis, p.id);
  // }

  int ctr = 0, cto = 0, cbr = 0, cbo = 0;
  for(point p : up) ctr += p.jenis, cto += !p.jenis;
  for(point p : low) cbr += p.jenis, cbo += !p.jenis;

  int ctr2 = ctr, cto2 = cto, cbr2 = cbr, cbo2= cbo;

  int id = -1;
  int mid = 1e9;

  int szu = up.size(), szl = low.size();
  int btm = 0;

  for(int top = 0; top < szu; top++) {
    point t = up[top];
    while(btm < szl && cross2(t, low[btm]) > 0) {
      bool jenis = low[btm].jenis;
      ctr += jenis, cto += !jenis;
      cbr -= jenis, cbo -= !jenis;
      btm += 1;
    }

    ctr -= t.jenis, cto -= !t.jenis;

    // printf("%d %d %d %d\n",ctr, cto, cbr, cbo);
    if (t.jenis != pick.jenis && ctr == cto && cbr == cbo) {
      if (max(ctr, cbr) < mid) {
        // printf("hahaa\n");
        mid = max(ctr, cbr);
        id = up[top].id;
      }
    }
    
    cbr += t.jenis, cbo += !t.jenis;
  }

  int top = 0;
  for(int bot = 0; bot < szl; bot++) {
    point b = low[bot];
    while(top < szu && cross2(b, up[top]) > 0) {
      bool jenis = up[top].jenis;
      ctr2 -= jenis, cto2 -= !jenis;
      cbr2 += jenis, cbo2 += !jenis;
      top += 1;
    }

    cbr2 -= b.jenis, cbo2 -= !b.jenis;
    if (b.jenis != pick.jenis && ctr2 == cto2 && cbr2 == cbo2) {
      if (max(ctr2, cbr2) < mid) {
        mid = max(ctr2, cbr2);
        id = low[bot].id;
      }
    }
    
    ctr2 += b.jenis, cto2 += !b.jenis;
  }

  // printf("%d\n",id);

  return id;
}

void solve(vector<point> all) {
  int sz = all.size();
  if (sz == 0) return;
  
  // printf("point to be processed\n");
  // for(point p : all) {
  //   printf("%d %d %d\n",p.x, p.y, p.id);
  // }

  // cin.ignore(); cin.ignore();

  if (sz == 2) {
    if (all[0].jenis) {
      match[all[0].id] = all[1].id;
    } else {
      match[all[1].id] = all[0].id;
    }
    return;
  }

  int picked = rand()%sz;
  int ret = 0;
  while((ret = solve2(all, picked, sz)) == -1) {
    picked = rand()%sz;
  }

  for(int i = 0; i < sz; i++) {
    if (ret == all[i].id && all[i].jenis != all[picked].jenis) {
      ret = i;
      break;
    }
  }

  
  if (all[picked].jenis) {
    // printf("match %d %d\n",all[picked].id, all[ret].id);
    match[all[picked].id] = all[ret].id;
  } else { 
    // printf("match %d %d\n",all[ret].id, all[picked].id);
    match[all[ret].id] = all[picked].id;
  }
  // printf("%d %d\n",all[picked].x, all[picked].y);
  // printf("%d %d\n",all[ret].x, all[ret].y);

  // cin.ignore(); cin.ignore();

  vector<point> left, right;

  for(int i = 0; i < sz; i++) {
    if (i == picked || i == ret) continue;
    if (cross(all[picked], all[ret], all[i]) > 0) {
      left.push_back(all[i]);
    } else {
      right.push_back(all[i]);
    }
  }

  solve(left);
  solve(right);
}

int main() {
  srand(time(NULL));

  scanf("%d",&tc);
  while(tc--) {
    scanf("%d",&n);

    vector<point> rocket;
    for(int i = 1; i <= n; i++) {
      int x, y;
      scanf("%d %d",&x, &y);
      rocket.push_back(point(x, y, i, true));
    }

    for(int i = 1; i <= n; i++) {
      int x, y;
      scanf("%d %d",&x, &y);
      rocket.push_back(point(x, y, i, false));
    }

    memset(match, 0, sizeof match);

    solve(rocket);

    for(int i = 1; i <= n; i++) {
      printf("%d\n",match[i]);
    }
  }
  return 0;
}