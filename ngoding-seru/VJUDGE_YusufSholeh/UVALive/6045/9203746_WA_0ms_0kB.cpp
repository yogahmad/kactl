#include<bits/stdc++.h>
using namespace std;

const int MAX = 100006;
const int TMAX = 4*MAX;

typedef pair<int,int> pii;
typedef pair<int,pii> point;
#define y first
#define x second.first
#define index second.second
#define mp make_pair
#define INF 1e9
#define LL long long

int N, Q, W, H;
int Ek, a, b, c, d, e, f;

void transform(point &p) { // move person
	// printf("ASGASGAS %d\n",(p.x + p.y));
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
	
	int delete_point(int sy, int ey) {
		multiset<point>::iterator tmp, it = mset.lower_bound(mp(sy, mp(-INF, 0)));
		
		int num_of_deleted = 0;
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

void update(int now, int l, int r, point p) {
	segtree[now].insert_point(p);
	if (l == r) return;
	
	int mid = (l + r) >> 1;
	if (p.x <= mid) update(now << 1, l, mid, p);
	else			update(now << 1 | 1, mid + 1, r, p);
}

void query(int now, int l, int r, int sx, int ex, int sy, int ey) {
	if (r < sx || l > ex) return;
	
	// printf("WTF %d %d\n",l, r);
	
	if (sx <= l && r <= ex) {
		int num_of_deleted = segtree[now].delete_point(sy, ey);
		if (num_of_deleted == 0) return;
	}
	if (l == r) return;
	
	int mid = (l + r) >> 1;
	
	query(now << 1, l, mid, sx, ex, sy, ey);
	query(now << 1 | 1, mid + 1, r, sx, ex, sy, ey);
}

point trans[MAX];
point input[MAX];

int main() {
	int tc;
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%d %d %d %d",&N, &Q, &W, &H);
		
		for(int i = 1; i <= N; i++) {
			scanf("%d %d",&input[i].x, &input[i].y);
			input[i].index = i;
			
			trans[i].index = i; // copy input transformation
			trans[i].x = input[i].x + input[i].y;
			trans[i].y = input[i].x - input[i].y;
			update(1, 0, MAX, trans[i]); // update segtree
		}
		
		for(int i = 1; i <= Q; i++) {
			int qx, qy;
			scanf("%d %d",&qx, &qy);
			scanf("%d %d %d %d %d %d %d",&Ek, &a, &b, &c, &d, &e, &f);
			
			int lx = max(  0,qx + qy - Ek);
			int rx = min(MAX,qx + qy + Ek);
			int ly = qx - qy - Ek; // ini di taruh set jadi ga usah max min
			int ry = qx - qy + Ek; // ini di taruh set jadi ga usah max min
			
			pending_move.clear();
			
			query(1, 0, MAX, lx, rx, ly, ry);
			
			int size_pending = pending_move.size();
			
			// printf("ABDUCTION #%d:\n",i);
			for(int i = 0; i < size_pending; i++) {
				point now = pending_move[i];
				done_index[now.index] = false;
				
				// printf("move from %d %d\n",(now.x + now.y)/2, (now.x - now.y)/2);
				
				transform(now);	// MOVE BY ALIEN
				update(1, 0, MAX, now);
				trans[now.index] = now;
				int getx = (trans[i].x + trans[i].y)/2;
				// printf("to %d %d\n",getx, trans[i].x - getx);
			}
			
		}
		
		printf("Case #%d:\n",cs);
		
		for(int i = 1; i <= N; i++) {
			int getx = (trans[i].x + trans[i].y)/2;
			assert(getx >= 0 && trans[i].x - getx >= 0);
			printf("%d %d\n",getx, trans[i].x - getx);
		}
		
		/** CLEAR **/
		for(int i = 0; i < TMAX; i++) segtree[i].mset.clear();
		memset(done_index, false, sizeof(done_index));
	}
	
	return 0;
}