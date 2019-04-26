#include<bits/stdc++.h>
using namespace std;
#define MAX 1000

const int off = 400;
int depth = -1;
int max_d = 0;
int r, c;
bool row[MAX], col[MAX], rc[MAX][MAX], diag1[400], diag2[405];
char maps[MAX][MAX];

void dfs(int x, int y, int step) {
	if (depth != -1) return;
	if (step == max_d) {
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				if (maps[i][j] == 'X') {
					if (diag1[i-j+off] || diag2[i+j] || row[i] || col[j]) {
						
					} else {
						return;
					}
				}
			}
		}
		depth = step;
		return; 
	}
	if (y == c) y = 0, x++;
	if (x == r) return;
	diag1[x-y+off] = true;
	row[x] = true; 
	col[y] = true;
	diag2[x+y] = true;
	rc[x][y] = true;
	dfs(x, y + 1, step + 1);
	diag1[x-y+off] = false;
	row[x] = false; 
	col[y] = false;
	diag2[x+y] = false;
	rc[x][y] = false;
	dfs(x, y + 1, step);
}

int main() {
	int cs = 0;
	while(true) {
		scanf("%d",&r);
		if (r == 0) break;
		scanf("%d",&c);
		for(int i = 0; i < r; i++) 
			scanf("%s",&maps[i]);
		
		memset(diag1,false,sizeof(diag1)); 
		memset(diag2,false,sizeof(diag2));
		memset(row, false, sizeof(row));
		memset(col, false, sizeof(col));
		memset(rc, false, sizeof(rc));
		depth = -1;
		for(int i = 0; i < 6; i++) {
			max_d = i;
			dfs(0, 0, 0);
			if (depth != -1) {
				break;
			}
		}
		
		cs++;
		printf("Case %d: ",cs);
		if (depth != -1) printf("%d\n",depth);
		else printf("6\n");
	}
}