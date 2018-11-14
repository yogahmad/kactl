/**
 * Author: Yusuf Sholeh
 * Date: 2018-08-08
 * Description: Rotational sweeping based on origin. Remove the origin.
 * Useful for many calculations such as total area of possible triangle.
 * Status: tested
 * Time: $O(N \log N)$
 */

ll cross2(point p, point r) {
  return p.x * r.y - p.y * r.x;
}

// 2 points seen on the same angle will be sorted based on closest to origin.
bool cmp(point a, point b) {
  if (a.y == 0 && b.y == 0) {
    if (a.x * b.x >= 0) return a.x*a.x+a.y*a.y < b.x*b.x+b.y*b.y;
    return a.x > b.x; // x+ first
  }
  if (cross2(a,b) == 0) return a.x*a.x+a.y*a.y < b.x*b.x+b.y*b.y;
  return cross2(a, b) > 0; 
}

// return a vector rotated ccw, from positive x-axis, and id being removed from vector.
vector<point> rotational_sweep(vector<point> &all, int id) {
	vector<point> up, low;
  for(int i = 0; i < sz(all); i++) if (i != id) {
    point p = all[i];
    p.x -= all[id].x, p.y -= all[id].y;
    if (p.y >= 0) up.push_back(p); // point on y==0 will treated on top
    else low.push_back(p);
  }
  sort(up.begin(), up.end(), cmp);
  sort(low.begin(), low.end(), cmp);
	vector<point> res = up;
	for(auto cur : low) res.push_back(cur);
  return res;
}

// apply this : last podal lie on the same line.
// note : true if segment a..b contain origin, or a.dist2() < b.dist2()
inline bool collinear_sweep(point a, point b) { 
  if (cross2(a,b) != 0) return false;
  if ((a.x < 0 && b.x > 0) || (a.y < 0 && b.y > 0)) return true;
  if ((a.x == 0 && a.y == 0) || (b.x == 0 && b.y == 0)) return true;
  return a.x*a.x+a.y*a.y < b.x*b.x+b.y*b.y;
}

void process(vector<point> &cur, int id) { // total area of possible triangle:
  vector<point> rot = rotational_sweep(cur, id);
  int size = sz(rot);

  ll sum_rx = rot[0].x, sum_ry = rot[0].y;

  // do rotate with i being the podal, r with the last podal 
  // important: check whether there is collinear (:check the quadrant!)
  for(int i = 0, r = 0; i < size; i++) {
    while(cross2(rot[i], rot[(r+1)%size]) > 0 ||
      collinear_sweep(rot[i], rot[(r+1)%size])) { // toggle this

      r = (r + 1)%size;
      // do something
      sum_rx += rot[r].x, sum_ry += rot[r].y;
    }    
    // process i..r:
    ans += rot[i].x * sum_ry - rot[i].y * sum_rx;
    // after process i..r, do cancel:
    sum_rx -= rot[i].x, sum_ry -= rot[i].y;
    if (i == r) {
      r = (i+1)%size;
      sum_rx = rot[r].x, sum_ry = rot[r].y;
    }
  }   
}
