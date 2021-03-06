#include<bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define MAX 200005
#define MAXC 1000010
using namespace std;

typedef pair<int,int> pii;

struct point{
	int x, y, id, event;
	point(){};
	point(int _x, int _y, int _id, int _event){
		x = _x, y = _y, id = _id, event = _event;
	}
};

point A[MAX*2];
point B[MAX*2];

int tc;
int ans[MAX*2];


bool cmp1(point a, point b) {
	return a.x < b.x;
}

bool cmp2(point a, point b) {
	return a.y < b.y;
}

int XX, YY;
pii X[MAXC*2 + 10], Y[MAXC*2 + 10];
bool bolx[MAXC*2 + 10], boly[MAXC*2 + 10];

int main() {
	
	for(int i = 0; i < MAXC+MAXC; i++)
		X[i] = mp(0, 0),
		Y[i] = mp(0, 0);
	
	scanf("%d",&tc);
	
	for(int cs = 1; cs <= tc; cs++) {
		int t, p;
		scanf("%d %d",&t, &p);
		
		//if (cs == 96) printf("%d %d\n",t, p);
		
		assert(t <= 100000 && p <= 100000);
		
		for(int i = 1; i <= t; i++) {
			int x, y;
			scanf("%d %d",&x, &y);
			
			//if (cs == 96) printf("%d %d\n", x, y);
			assert(x >= -1000000 && x <= 1000000);
			assert(y >= -1000000 && y <= 1000000);
			x += MAXC;
			y += MAXC;
			bolx[x] = true;
			boly[y] = true;
			A[i] = point(x, y, i, 0);
			B[i] = point(x, y, i, 0);
		}
		
		XX = t, YY = t;
		for(int i = 1; i <= p; i++) {
			char op[20];
			int val;
			scanf("%s%d",&op, &val);
			//if (cs == 96) printf("%s %d\n",op, val);
			
			assert(val >= -1000000 && val <= 1000000);
			val += MAXC;
			
			if (op[0] == 'H' && boly[val])
				assert(false);
			if (op[0] == 'V' && bolx[val])
				assert(false);
			
			if (op[0] == 'H') {
				YY++;
				B[YY] = point(val, val, 0, 1);
			} else {
				XX++;
				A[XX] = point(val, val, 0, 1);
			}
		}
		
		sort(A + 1, A + XX + 1, cmp1);
		sort(B + 1, B + YY + 1, cmp2);
			
		memset(ans, 0 ,sizeof(ans));
		
		//printf("------------\n");
		
		int ada = 0;
		for(int i = 1; i <= XX; i++) {
			//printf("%d %d\n",A[i].x, ada);
			if (A[i].event == 1) {
				ada++;
			} else {
				int ye = A[i].y;
				if (Y[ye].f == ada)
					Y[ye].s = A[i].id;
				else {
					ans[Y[ye].s] += 1;
					ans[A[i].id] += 1;
					//printf("%d %d\n",Y[ye].s, A[i].id);
					Y[ye] = mp(ada, A[i].id);
				}
			}
		}
		//printf("\n ------------\n");
		
		int ada2 = 0;
		for(int i = 1; i <= YY; i++) {
			//printf("%d %d\n",B[i].y, ada);
			if (B[i].event == 1) {
				ada2++;
			} else {
				int ix = B[i].x;
				if (X[ix].f == ada2)
					X[ix].s = B[i].id;
				else {
					ans[X[ix].s] += 1;
					ans[B[i].id] += 1;
					X[ix] = mp(ada2, B[i].id);
				}
			}
		}
		
		for(int i = 1; i <= 2000020; i++) {
			if (Y[i].f != ada)
				ans[Y[i].s] += 1;
			Y[i] = mp(0,0);
			
			if (X[i].f != ada2)
				ans[X[i].s] += 1;
			X[i] = mp(0,0);
			
			bolx[i] = false;
			boly[i] = false;
		}
		
		int res = 0;
		for(int i = 1; i <= t; i++) {
			assert(ans[i] <= 4);
			if (ans[i] > 0)
				res++;
		}
		
		//printf("%d\n",res);
		assert(res > 0);
		//printf("%d %.5lf ",res, (double)res/t);
		printf((5*res >= 3*t) ? "PASSED\n" : "FAILED\n");
	}
	
	
}