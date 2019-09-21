#include<bits/stdc++.h>
using namespace std;


#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define pb push_back

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int ret;
	scanf("%d",&ret);
	return ret;
}

#define LL long long
#define MAX 100005
#define INF 10000000

char ans[2550][4];

int main(){
	// freopen("black.in", "r", stdin);
	// freopen("black.out", "w", stdout);
	
	int w, b;
	cin >> w >> b;
	
	int ampas = max(w,b)*2 + 5;
	for(int i = 0; i < ampas; i++) {
		ans[i][0] = '.';
		ans[i][1] = '.';
		ans[i][2] = '@';
		ans[i][3] = '@';
	}
	w--; b--;
	int ptr = 0;
	while(b > 0) { b--;
		ans[ptr][0] = '@';
		ptr += 2;
	}
	ptr = 0;
	while(w > 0) { w--;
		ans[ptr][3] = '.';
		ptr += 2;
	}
	
	for(int i = 0; i < ampas; i++) printf("%c%c%c%c\n",ans[i][0],ans[i][1],ans[i][2],ans[i][3]);
}
