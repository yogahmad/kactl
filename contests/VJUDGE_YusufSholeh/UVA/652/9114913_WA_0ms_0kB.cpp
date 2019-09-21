#include<bits/stdc++.h>
using namespace std;

int n; int tc; int inp[10];

struct grid{
	int px, py;
	int predict;
	int ampas[3][3];
	vector<char> res;
	
	void print() {
		printf("/** =============== **/\n");
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if (ampas[i][j] == 9) printf("x ");
				else printf("%d ",ampas[i][j]);
			}
			printf("\n");
		}
	}
};

queue<grid> pq;

map<int, vector<char> > maps;
map<int, int> Hash;
void move(grid New, int dx, int dy) {
	if (New.px + dx < 0 || New.py + dy < 0 || New.px + dx >= 3 || New.py + dy >= 3) return;
	swap(New.ampas[New.px][New.py], New.ampas[New.px + dx][New.py + dy]);
	
	int bzz = 0;
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
		int val = New.ampas[i][j];
		bzz = 10*bzz + val;
	}
			
	if(Hash.count(bzz)) return;
	// printf("%d\n",bzz);
	Hash[bzz] += 1;
	maps[bzz] = New.res;
	New.predict = bzz;
	if (dx == 1 && dy == 0) New.res.push_back('d');
	else if (dx == 0 && dy == 1) New.res.push_back('r');
	else if (dx == 0 && dy ==-1) New.res.push_back('l');
	else if (dx ==-1 && dy == 0) New.res.push_back('u');
	New.px += dx; New.py += dy;
	pq.push(New);
}

void precomp() {
	grid start;
	for(int i = 0; i < 9; i++) start.ampas[i/3][i%3] = i+1;
	start.px = 2; start.py = 2;
	bool ada = false;
	pq.push(start);
	while(!pq.empty()) {
		grid top = pq.front(); pq.pop();
		move(top, 1, 0);
		move(top, 0, 1);
		move(top,-1, 0);
		move(top, 0,-1);
	}
	Hash.clear();
}

int main() {
	
	precomp();
	
	int bs = 0;
	scanf("%d",&tc); getchar();
	while(tc--) {
		if (bs) printf("\n");
		bs++;
		char dmb; getchar();
		for(int i = 0; i < 9; i++) {
			char fak; fak = getchar();
			inp[i] = (int)fak - '0';
			if (inp[i] == 72) inp[i] = 9;
			getchar();
		}
			
		int angka = 0;
		for(int i = 0; i < 9; i++) angka = 10*angka + inp[i];
		
		if (maps.count(angka)) {
			vector<char> res = maps[angka];
			for(int i = 0; i < res.size(); i++) 
				printf("%c",res[i]);
			printf("\n");
		} else {
			printf("unsolvable\n");
		}
		
	}
}