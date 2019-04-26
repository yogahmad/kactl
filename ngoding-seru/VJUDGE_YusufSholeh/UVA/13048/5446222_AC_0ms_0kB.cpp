#include<bits/stdc++.h>
using namespace std;
char ch[105];
int main() {
	int tc;
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%s",ch);
		int len = strlen(ch);
		int ans = 0;
		for(int i = 0; i < len; i++) {
			if (ch[i] == '-') {
				if (i + 1 < len  && (ch[i + 1] == 'S' || ch[i + 1] == 'B')) continue;
				if (i - 1 >= 0   && (ch[i - 1] == 'S')) continue;
				if (i + 2 < len  && (ch[i + 2] == 'B')) continue;
				ans += 1;				
			}
		}
		printf("Case %d: %d\n",cs,ans);
	}
}