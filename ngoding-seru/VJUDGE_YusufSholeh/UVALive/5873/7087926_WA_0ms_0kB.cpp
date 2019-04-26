#include<bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define MAX 100005
#define MAXC 1000005
using namespace std;

typedef pair<int,int> pii;

struct point{
	int x, y, id, event;
	point(){};
	point(int _x, int _y, int _id, int _event){
		x = _x, y = _y, id = _id, event = _event;
	}
};

point A[MAX];
point B[MAX];

int tc;
bool ans[MAX];

bool cmp1(point a, point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

bool cmp2(point a, point b) {
	if (a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

int XX, YY;
pii X[MAXC+MAXC], Y[MAXC+MAXC];

int main() {
	
	for(int i = 0; i < MAXC+MAXC; i++)
		X[i] = mp(0, -1),
		Y[i] = mp(0, -1);
	
	scanf("%d",&tc);
	while(tc--) {
		int t, p;
		scanf("%d %d",&t, &p);
		
		for(int i = 1; i <= t; i++) {
			int x, y;
			scanf("%d %d",&x, &y);
			x += MAXC-4;
			y += MAXC-4;
			A[i] = point(x, y, i, 0);
			B[i] = point(x, y, i, 0);
		}
		
		XX = t, YY = t;
		for(int i = 1; i <= p; i++) {
			char op;
			int val;
			getchar();
			scanf("%c %d",&op, &val);
			val += MAXC-4;
			
			if (op == 'H') 
				B[++YY] = point(val, val, i, 1);
			else 
				A[++XX] = point(val, val, i, 1);
		}
		
		sort(A + 1, A + XX + 1, cmp1);
		sort(B + 1, B + YY + 1, cmp2);
			
		memset(ans, false,sizeof(ans));
		
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
					ans[max(0,Y[ye].s)] = true;
					ans[A[i].id] = true;
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
					ans[max(0,X[ix].s)] = true;
					ans[B[i].id] = true;
					//printf("%d %d\n",X[ix].s, B[i].id);
					X[ix] = mp(ada2, B[i].id);
				}
			}
		}
		
		for(int i = 0; i < MAXC + MAXC; i++) {
			int ye = i;
			if (Y[ye].f != ada)
				ans[max(0,Y[ye].s)] = true;
			Y[ye] = mp(0,-1);
			
			int ix = i;
			if (X[ix].f != ada2)
				ans[max(0,X[ix].s)] = true;
			X[ix] = mp(0,-1);
		}
		
		int res = 0;
		for(int i = 1; i <= t; i++)
			if (ans[i])
				res++;
		
		//printf("%d\n",res);
		printf((5*res >= 3*t) ? "PASSED\n" : "FAILED\n");
	}
	
}