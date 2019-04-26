#include<bits/stdc++.h>
using namespace std;

#define LL long long
const LL MAX = 70006;
const LL TMAX = 4*MAX;

typedef pair<LL,LL> pii;
typedef pair<LL,pii> point;
#define y first
#define x second.first
#define index second.second
#define mp make_pair
#define INF 1e18

LL N, Q, W, H;
LL Ek, a, b, c, d, e, f;

void transform(point &p) { // move person
	// printf("ASGASGAS %lld\n",(p.x + p.y));
	LL tmpx = (p.x + p.y)/2, tmpy = p.x - tmpx; // GET ORI COORD
	p.x = ( (LL)tmpx * a + (LL)tmpy * b + (LL)p.index * c) % W;
	p.y = ( (LL)tmpx * d + (LL)tmpy * e + (LL)p.index * f) % H;
	tmpx = p.x;
	p.x = p.x + p.y;	// TURN BACK TO DIAMOND COORD
	p.y = tmpx - p.y;
}

bool done_index[MAX];
vector<point> pending_move;

struct inner{
	multiset<point> mset;
	
	void insert_point(point p) {
		mset.insert(p);
	}
	
	LL delete_point(LL sy, LL ey) {
		multiset<point>::iterator tmp, it = mset.lower_bound(mp(sy, mp(-INF, 0)));
		
		LL num_of_deleted = 0;
		while (it != mset.end() && it->y <= ey) {
			tmp = it;
			it++;
			num_of_deleted += 1;
			
			if (!done_index[tmp->index]) {
				done_index[tmp->index] = true;
				pending_move.push_back(*tmp);
			}
			mset.erase(tmp); 
		}
		
		return num_of_deleted;
	}
	
} segtree[TMAX];

void update(LL now, LL l, LL r, point p) {
	segtree[now].insert_point(p);
	if (l == r) return;
	
	LL mid = (l + r) >> 1;
	if (p.x <= mid) update(now*2, l, mid, p);
	else			update(now*2 + 1, mid + 1, r, p);
}

void query(LL now, LL l, LL r, LL sx, LL ex, LL sy, LL ey) {
	if (r < sx || l > ex) return;
	
	// printf("WTF %lld %lld\n",l, r);
	
	if (sx <= l && r <= ex) {
		LL num_of_deleted = segtree[now].delete_point(sy, ey);
		if (num_of_deleted == 0) return;
	}
	if (l == r) return;
	
	LL mid = (l + r) >> 1;
	
	query(now*2, l, mid, sx, ex, sy, ey);
	query(now*2 + 1, mid + 1, r, sx, ex, sy, ey);
}

point trans[MAX];
point input[MAX];

int main() {
	LL tc;
	scanf("%lld",&tc);
	for(LL cs = 1; cs <= tc; cs++) {
		scanf("%lld %lld %lld %lld",&N, &Q, &W, &H);
		
		for(LL i = 1; i <= N; i++) {
			scanf("%lld %lld",&input[i].x, &input[i].y);
			input[i].index = i;
			
			trans[i].index = i; // copy input transformation
			trans[i].x = input[i].x + input[i].y;
			trans[i].y = input[i].x - input[i].y;
			update(1, 0, MAX, trans[i]); // update segtree
		}
		
		for(LL i = 1; i <= Q; i++) {
			LL qx, qy;
			scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld",&qx, &qy, &Ek, &a, &b, &c, &d, &e, &f);
			
			LL lx = max(0LL,qx + qy - Ek);
			LL rx = min(MAX,qx + qy + Ek);
			LL ly = qx - qy - Ek; // ini di taruh set jadi ga usah max min
			LL ry = qx - qy + Ek; // ini di taruh set jadi ga usah max min
			
			pending_move.clear();
			
			query(1, 0, MAX, lx, rx, ly, ry);
			
			LL size_pending = pending_move.size();
			
			// printf("ABDUCTION #%lld:\n",i);
			for(LL i = 0; i < size_pending; i++) {
				point now = pending_move[i];
				done_index[now.index] = false;
				
				// printf("move from %lld %lld\n",(now.x + now.y)/2, (now.x - now.y)/2);
				
				transform(now);	// MOVE BY ALIEN
				update(1, 0, MAX, now);
				trans[now.index] = now;
				LL getx = (trans[i].x + trans[i].y)/2;
				// printf("to %lld %lld\n",getx, trans[i].x - getx);
			}
			
		}
		
		printf("Case #%lld:\n",cs);
		
		for(LL i = 1; i <= N; i++) {
			LL getx = (trans[i].x + trans[i].y)/2;
			printf("%lld %lld\n",getx, trans[i].x - getx);
		}
		
		/** CLEAR **/
		for(LL i = 0; i < TMAX; i++) segtree[i].mset.clear();
		memset(done_index, false, sizeof(done_index));
	}
	
	return 0;
}