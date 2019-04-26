#include<bits/stdc++.h>
using namespace std;

struct Matrix{
	int r, c;
	char huruf;
};

vector<Matrix> v;
Matrix input[30];

int main() {
	int n;
	scanf("%d",&n); getchar();
	for(int i = 0; i < n; i++) {
		char tmp;
		int x, y;
		scanf("%c %d %d",&tmp, &x, &y); getchar();
		Matrix INP;
		INP.huruf = tmp;
		INP.r = x;
		INP.c = y;
		input[INP.huruf-'A'] = INP;
		// printf("%c %d %d\n",input[tmp-'A'].huruf, input[tmp-'A'].r, input[tmp-'A'].c);
	}
	
	char s[1005];
	while(scanf("%s",s) != EOF) {
		int len = strlen(s);
		int ans = 0;
		v.clear();
		for(int i = 0; i < len; i++) {
			if (isalpha(s[i])) {
				v.push_back(input[s[i]-'A']);
			} else if (s[i] == ')') {
				if (v.size() < 2) {
					printf("error\n");
					goto END;
				}
				Matrix B = v[v.size()-1]; v.pop_back();
                Matrix A = v[v.size()-1]; v.pop_back();	
                if(A.c != B.r){
					printf("error\n");
                    goto END;
                }
				Matrix res;
				res.r = A.r;
				res.c = B.c;
                ans += A.r * A.c * B.c;
				v.push_back(res);
			}
		}
		printf("%d\n",ans);
		END:;
	}
	
	return 0;
}