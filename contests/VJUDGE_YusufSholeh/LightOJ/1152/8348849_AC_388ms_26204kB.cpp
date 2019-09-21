#include <bits/stdc++.h>
using namespace std;

const int N = 50;

char cell[N][N];

vector <int> V[N*N], kiri;
int done[N*N], bip[N][N], cek[N][N][N][N], visit[N*N], owner[N*N];

int x[] = {0, 0, 1, -1};
int y[] = {1, -1, 0, 0};

bool matching(int u){

	if(visit[u] == 1)
		return false;

	visit[u] = 1;

	for(int i=0; i<V[u].size(); i++){
		int v = V[u][i];
		if(owner[v] == -1 || matching(owner[v])){
			owner[v] = u;
			return true;
		}
	}

	return false;
}

int main(){
	int t, tt = 0;
	scanf("%d", &t);

	while(t--){
		int n, m;
		scanf("%d %d", &n, &m);

		memset(done, 0, sizeof(done));
		memset(cek, 0, sizeof(cek));
		memset(bip, 0, sizeof(bip));
		memset(owner, -1, sizeof(owner));
		kiri.clear();

		for(int i=0; i<N*N; i++)
			V[i].clear();

		for(int i=0; i<n; i++)
			scanf("%s", cell[i]);

		int num = 1, sum = 0;

		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++){
				bip[i][j] = num++;
				if(cell[i][j] == '*')
					sum++;
			}

		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){

				if(cell[i][j] != '*')
					continue;

				for(int k=0; k<4; k++){
					int rr = i + x[k];
					int cc = j + y[k];

					if(0 <= rr && rr < n && 0 <= cc & cc < m && cek[i][j][rr][cc] == 0 && cell[rr][cc] == '*'){
						cek[i][j][rr][cc] = 1;
						cek[rr][cc][i][j] = 1;

						if((i + j)%2 == 1){
							V[bip[i][j]].push_back(bip[rr][cc]);
							if(done[bip[i][j]] == 0){
								kiri.push_back(bip[i][j]);
								done[bip[i][j]] = 1;
							}
						}
						else{
							V[bip[rr][cc]].push_back(bip[i][j]);
							if(done[bip[rr][cc]] == 0){
								kiri.push_back(bip[rr][cc]);
								done[bip[rr][cc]] = 1;
							}
						}
					}
				}
			}
		}

		int match = 0;

		for(int i=0; i<kiri.size(); i++){
			int u = kiri[i];

			memset(visit, 0, sizeof(visit));
			if(matching(u))
				match++;
		}

		// printf("match = %d, sum = %d\n", match, sum);

		printf("Case %d: %d\n", ++tt, sum - match);
	}

	return 0;
}