#include<bits/stdc++.h>
#define LL long long
#define EPS 1e-8
using namespace std;
LL n , w;
LL wi[2005], ti[2005], del[2005];
LL A[2005], B[2005];
LL res[10005];
LL dp[10005];
double res2[10005];

typedef pair<LL,LL> pii;
#define f first
#define s second
#define mp make_pair

struct line{
	LL m, c;
	line () {};
	line(LL _m, LL _c) {
		m = _m, c = _c;
	}
	LL getval(LL x) {
		return m*x + c;
	}
};

vector<line> v;
LL cur;

inline bool bad(line a, line b, line c) {
	return (b.c - a.c)*(b.m - c.m) >= (c.c - b.c)*(a.m - b.m);
}

inline void add(LL grad, LL konstanta) {
	line present = line(grad, konstanta);
	while(v.size() >= 2 && bad( v[v.size() - 2], v[v.size() - 1], present)) v.pop_back();
	v.push_back(present);
}

inline LL get(LL x) {
	if (v.size() == 0) return 0;
	if (cur >= v.size()) cur = v.size() - 1;
	while(cur < v.size() - 1 && v[cur].getval(x) < v[cur+1].getval(x)) cur++;
	return v[cur].getval(x);
}

LL tc;

pii integ[2005];

bool cmp(pii a, pii b) {
	if (a.f == b.f) return a.s < b.s;
	return a.f > b.f;
}

int main() {
	
	//scanf("%d",&tc);
	
	for(LL i = 0; i < 10005; i++) res[i] = -1e15, res2[i] = 0;
	
	LL N;
	while(scanf("%lld %lld",&N, &w) != EOF) {
		LL n2 = 0;
		n = 0;
		for(LL i = 1; i <= N; i++) {
			char op[50];
			scanf("%s",&op);
			
			if (op[0] == 'D') {
				n++;
				scanf("%lld %lld %lld",&wi[n], &ti[n], &del[n]);
			} else {
				n2++;
				scanf("%lld %lld",&integ[n2].f, &integ[n2].s);
			}
		}
		
		res[0] = 0;
		for(LL k = 1; k <= n; k++) {
			LL d = del[k];
			LL t = ti[k];
			LL W = wi[k];
			for(LL mod = 0; mod < W; mod++) {
				LL q = (w - mod)/W + 1;
				v.clear();
				cur = 0;
				
				for(LL i = 1; i <= q; i++) {
					LL weight = (i-1)*W + mod;
					dp[i] = -1e15;
					if (i != 1) {
						LL now = i*(i - 1)/2;
						now = -(now * d)+ i*t + get(i);
						dp[i] = now;
					}
					long long konstanta = i*(i + 1)/2;
					konstanta = -(konstanta*d) - i * t + res[weight];
					add(i*d, konstanta);
					
					if (dp[i] > res[weight]) res[weight] = dp[i];
					//printf("%d %d %d\n",i, weight, res[weight]);
				}
			}
		}
		
		// mungkLL t = 0
		bool impossible = (n2 == 0 && res[w] <= -1e10);
		//printf("%d\n",impossible);
		
		for(LL i = 1; i <= w; i++) 
			res2[i] = 0;
		
		sort(integ + 1, integ + n2 + 1, cmp);
		
		
		for(LL i = 1; i <= w; i++) {
			double sisa = i;
			double sum = 0;
			LL seb = integ[1].f;
			LL last = 1;
			double dx = 0;
			bool adanol = false;
			for(LL j = 1; j <= n2; j++) {
				if (integ[j].f != seb) {
					double ngurang = sum * (seb - integ[j].f);
					
					if (sisa - ngurang >= -EPS) {
						sisa -= ngurang;
						seb = integ[j].f;
					} else break;

				}
				last = j;
				if (integ[j].s == 0) {
					adanol = true;
					dx = integ[j].f;
					break;
				}
				sum += 1.0/integ[j].s;
			}
			
			for(LL j = 1; j <= last; j++) {
				if (adanol && j == last) break;
				double t = (double)(integ[j].f - seb)/integ[j].s;
				res2[i] += t*integ[j].f - t*t*(integ[j].s)/2;
			}
			
			if (adanol && sisa >= -EPS) {
				res2[i] += sisa * dx;
				//printf("%.5lf %.5lf %.5lf\n",res2[i], sisa, dx);
				continue;
			}
			
			if (sisa >= -EPS) {
				double x = sisa / sum;
				for(LL j = 1; j <= last; j++) {
					double t = x * (1.0/integ[j].s);
					res2[i] += t*seb - t*t*(integ[j].s)/2.0;
				}
			}
		}
		
		double ANS = -1e15;
		for(LL i = 0; i <= w; i++) {
			double sek =  res2[i] + res[w - i];
			
			if (sek > ANS) {
				ANS = sek;
				//printf("%d %d\n",i, w - i);
				//printf("%.5lf %d\n",res2[i], res[w - i]);
			}
			
			res[w - i] = -1e15;
			res2[i] = 0;
		}
		
		if (impossible) printf("impossible\n");
		else printf("%.9lf\n",ANS);
	}	
}