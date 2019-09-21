#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define pf push_front

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int has;
	scanf("%d",&has);
	return has;
}

#define LL long long
#define MAX 100005
#define MAXE 250005


double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);


int b, s;
int arr[505][505];
int nilai[505][505];

int main(){
	while(true) {
		scanf("%d %d",&s, &b);
		
		if (s == 0 && b == 0) {
			// printf("-\n");
			return 0;
		}
		set<pii> st;
		st.insert(mp(1,s));
		while(b--) {
			
			// for(set<pii> :: iterator X = st.begin(); X != st.end(); X++) {
				// printf("%d %d\n",(*X).f,(*X).s);
			// }
			
			int L, R;
			scanf("%d %d",&L, &R);
			if (st.size() == 0) {
				printf("* *\n");
				continue;
			}
			
			int ansL = -1, ansR = 1e9;
			st.insert(mp(L,R));
			set<pii>::iterator has = st.find(mp(L,R));
			set<pii>::iterator it = has; it++;
			while(it != st.end()) {
				pii now = *it;
				if (now.f > R) {
					ansR = min(ansR, now.f);
					break;
				} else {
					if (now.s <= R) {
						set<pii>::iterator tmp = it;
						it++;
						st.erase(tmp);
						continue;
					} else {
						ansR = min(ansR, R+1);
						st.erase(it);
						st.insert(mp(R+1, now.s));
						break;
					}
				}
			}
			it = has;
			set<pii>::iterator EraseLater;
			bool needErase = 0;
			while (it != st.begin()) {
				it--;
				if (needErase) st.erase(EraseLater),needErase = 0;
				pii now = *it;
				if (now.f == L) {
					if (now.s > R) {
						ansR = min(ansR, R+1);
						st.insert(mp(R+1,now.s));
					}
					EraseLater = it;
					needErase = 1;
					continue;
				}
				if (now.s < L) {
					ansL = max(ansL, now.s);
					break;
				} else {
					if (now.s > R) {
						ansR = min(ansR, R+1);
						ansL = max(ansL, L-1);
						st.erase(it);
						st.insert(mp(now.f,L-1));
						st.insert(mp(R+1,now.s));
						break;
					} else {
						ansL = max(ansL, L-1);
						st.erase(it);
						st.insert(mp(now.f,L-1));
						break;
					}
				}
			}
			
			if (needErase) st.erase(EraseLater);
			st.erase(st.find(mp(L,R)));
			if (ansL <= -1) printf("* "); 
			else printf("%d ",ansL);
			if (ansR == 1e9) printf("*\n");
			else printf("%d\n",ansR);
			
			// printf("QUERY %d %d\n",L, R); cin.ignore();
		}
		
		printf("-\n");
	}
}