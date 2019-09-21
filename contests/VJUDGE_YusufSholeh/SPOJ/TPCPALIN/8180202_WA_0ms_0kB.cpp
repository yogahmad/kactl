#include<bits/stdc++.h>
#define MOD 3210121
#define MAX 505
using namespace std;

int len1, len2;
int dp[MAX][MAX][MAX];
bool vis[MAX][MAX][MAX];
char s1[MAX], s2[MAX];

int f(int l1, int r1, int l2, int r2) {
	if (l1 >= r1 && l2 > r2) return 1;
	if (l1 > r1 && l2 >= r2) return 1;
	int &ret = dp[l1][r1][l2];
	if (vis[l1][r1][l2]) return ret; 
	vis[l1][r1][l2] = true; 
	if (l1 < r1 && s1[l1] == s1[r1]) ret += f(l1+1,r1-1,l2,r2);
	if (l2 < r2 && s2[l2] == s2[r2]) ret += f(l1,r1,l2+1,r2-1);
	if (l1 <= r1 && l2 <= r2){
		if (s1[l1] == s2[r2]) ret += f(l1+1,r1,l2,r2-1);
		if (s1[r1] == s2[l2]) ret += f(l1,r1-1,l2+1,r2);
	}
	return ret;
}
int main() {
	scanf("%s",&s1); scanf("%s",&s2);
	len1 = strlen(s1); len2 = strlen(s2);
	printf("%d\n",f(0,len1-1,0,len2-1));
	return 0;
}