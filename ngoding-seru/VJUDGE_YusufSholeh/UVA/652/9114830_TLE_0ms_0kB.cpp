#include<bits/stdc++.h>
using namespace std;

int n; int tc; int inp[10];

struct grid{
	int px, py;
	int predict;
	int ampas[3][3];
	vector<char> res;
	bool operator<(const grid& x)const{
		return predict > x.predict; 
	}
	inline void get_prediction() {
		int ans = 0;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				int angka = ampas[i][j] - 1;
				if (angka == 71) continue;
				int getx = angka/3;
				int gety = angka%3;
				ans += abs(getx - i) + abs(gety - j);
			}
		}
		predict = ans;
	}
	
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

map<int,int> Hash;
void move(grid New, int dx, int dy) {
	if (New.px + dx < 0 || New.py + dy < 0 || New.px + dx >= 3 || New.py + dy >= 3) return;
	swap(New.ampas[New.px][New.py], New.ampas[New.px + dx][New.py + dy]);
	
	int bzz = 0;
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
		int val = New.ampas[i][j];
		bzz = 10*bzz + val;
	}
			
	if(Hash.count(bzz)) return;
	Hash[bzz] += 1;
	
	New.predict = bzz;
	// printf("%d\n",bzz);
	// New.get_prediction();
	if (dx == 1 && dy == 0) New.res.push_back('d');
	else if (dx == 0 && dy == 1) New.res.push_back('r');
	else if (dx == 0 && dy ==-1) New.res.push_back('l');
	else if (dx ==-1 && dy == 0) New.res.push_back('u');
	New.px += dx; New.py += dy;
	// printf("%d %d %d\n",New.px, New.py, New.predict);
	pq.push(New);
}

int main() {
	int bs = 0;
	scanf("%d",&tc); getchar();
	while(tc--) {
		if (bs) printf("\n");
		bs++;
		char dmb; getchar();
		for(int i = 0; i < 9; i++) {
			char fak; fak = getchar();
			inp[i] = (int)fak - '0';
			getchar();
		}
	
		grid start;
		for(int i = 0; i < 9; i++) {
			// printf("%d\n",inp[i]);
			if (inp[i] == 72) {
				start.px = i/3, start.py = i%3;
				inp[i] = 9;
			}
			start.ampas[i/3][i%3] = inp[i];
		}
		// start.get_prediction();
		
		// printf("%d\n",start.predict);
		while(!pq.empty()) pq.pop();
		
		move(start, 0, 0);
		
		Hash.clear();
		bool ada = false;
		while(!pq.empty()) {
			grid top = pq.front(); pq.pop();
			// top.get_prediction();
			if (top.predict == 123456789) {
				int size = top.res.size();
				for(int i = 0; i < size; i++) printf("%c",top.res[i]);
				printf("\n");
				ada = true;
				break;
			}
			
			// top.print();
			
			move(top, 1, 0);
			move(top, 0, 1);
			move(top,-1, 0);
			move(top, 0,-1);
			
			
			/* printf("START !!\n");
			while(!pq.empty()) {
				int XX = pq.top().predict;
				printf("%d\n",XX);
				pq.pop();
			}  */ 
		}
		// printf("AMPAS\n");
		if (!ada) printf("unsolvable\n");
	}
}