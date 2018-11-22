/**
 * Author: Yusuf Sholeh
 * Date: 2018
 * License: UI
 * Description: Voronoi Diagram using Half Plane Intersection. For each point, do process.
 * Time: O(n^2 \log n)
 * Status: tested on kattis pandapreserve
 */

#include <Point.h>
#include <RotationalSweep.h>

struct line{ LD m, c; P where; bool straight; };
line make_line(P p) { 
  line ret; ret.where = p;
  if (fabs(p.y)<EPS) ret.straight = true, ret.c = p.x/2.0, ret.m = 1e9;
  else {
    ret.straight = false, ret.m = ((LD)-p.x)/p.y;
    ret.c = (-ret.m/2.0) * p.x + p.y/2.0;
  }
  return ret;
}
bool fine(line p, line q, line r) { // pot_p_q has different region with (0,0) seen from r
  LD px, py;
  if (p.where.cross(q.where)<=EPS||q.where.cross(r.where)<=EPS) return true;
  if (p.straight) px = p.c, py=q.m*p.c+q.c;
  else if (q.straight) px = q.c, py=p.m*q.c+p.c;
  else {px=(p.c-q.c)/(q.m-p.m); py=p.m*px+p.c;}
  if (r.straight && fabs(r.c-px) < EPS) return false;
  if (!r.straight && fabs(py-(r.m*px+r.c)) < EPS) return false;
  return r.straight? !((r.c+EPS>=0)^(r.c+EPS>=px)):!((0<=EPS+r.c)^(py-r.m*px<=EPS+r.c));
}
void process(vector<point> &po, int id) { // rotational up: x==0+ to x>0-. dn: x==0- to x<0+
  vector<point> rot = rotational_sweep(po, id); // if collinear, put largest distance first
  deque<line> res;
  for(point curr: rot) {
    line cur = make_line(curr);
    P bef = sz(res)>=1?res[sz(res)-1].where:P(0,0), aft = cur.where;
    if (sz(res)>=1 && bef.cross(aft) < -EPS) { res.push_back(cur); continue; }
    if (sz(res)>=1 && fabs(bef.cross(aft)) <= EPS && 
       fabs(bef.dist()+aft.dist()-(aft-bef).dist()) > EPS)
        res.pop_back();
    while(sz(res) >= 2 && !fine(res[sz(res)-2], res[sz(res)-1], cur)) 
      res.pop_back();
    res.push_back(cur);
  }
  while(sz(res)>=3) {
    bool e = false;
    while(sz(res)>=3&&!fine(res[sz(res)-2],res[sz(res)-1],res[0])) res.pop_back(),e=true;
    while(sz(res)>=3&&!fine(res.back(), res[0], res[1])) res.pop_front(),e=true;
    if (!e) break;
  }
  vector<P> v; res.push_back(res[0]);
  for(int i = 0; i < sz(res)-1; i++) {
    line cur = res[i], nxt = res[i+1];
    if (cur.where.cross(nxt.where) <= EPS) {
      LD zz = max(fabs(cur.where.x), fabs(cur.where.y));
      LD zz2 = max(fabs(nxt.where.x), fabs(nxt.where.y));
      zz = (zz > MAX) ? 1.0 : ceil(MAX/zz);
      zz2 = (zz2 > MAX) ? 1.0 : ceil(MAX/zz2);
      P mid1 = (cur.where/2.0).perp() * zz + (cur.where/2.0);
      P mid2 = (nxt.where/2.0).perp().perp().perp() * zz2 + (nxt.where/2.0);
      v.push_back(mid1+po[id]), v.push_back(mid2+po[id]);
    } else { 
      P pot; // assert(!cur.straight || !nxt.straight);
      if (cur.straight) pot.x = cur.c, pot.y = nxt.m*cur.c+nxt.c;
      else if (nxt.straight) pot.x = nxt.c, pot.y = cur.m*nxt.c+cur.c;
      else { pot.x = (nxt.c-cur.c)/(cur.m-nxt.m); pot.y = cur.m*pot.x+cur.c; }
      v.push_back(pot+po[id]);
    }   
  }
}
