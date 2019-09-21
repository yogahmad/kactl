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
				if (ampas[i][j] == 72) printf("x ");
				else printf("%d ",ampas[i][j]);
			}
			printf("\n");
		}
	}
};

priority_queue<grid> pq;

void move(grid New, int dx, int dy) {
	if (New.px + dx < 0 || New.py + dy < 0 || New.px + dx >= 3 || New.py + dy >= 3) return;
	swap(New.ampas[New.px][New.py], New.ampas[New.px + dx][New.py + dy]);
	New.get_prediction();
	if (dx == 1 && dy == 0) New.res.push_back('d');
	if (dx == 0 && dy == 1) New.res.push_back('r');
	if (dx == 0 && dy ==-1) New.res.push_back('l');
	if (dx ==-1 && dy == 0) New.res.push_back('u');
	New.px += dx; New.py += dy;
	// printf("%d %d %d\n",New.px, New.py, New.predict);
	pq.push(New);
}

int main() {
	scanf("%d",&tc); getchar();
	while(tc--) {
		char dmb; getchar();
		for(int i = 0; i < 9; i++) {
			char fak; fak = getchar();
			inp[i] = (int)fak - '0';
			getchar();
		}
	
		grid start;
		for(int i = 0; i < 9; i++) {
			// printf("%d\n",inp[i]);
			start.ampas[i/3][i%3] = inp[i];
			if (inp[i] == 72) start.px = i/3, start.py = i%3;
		}
		start.get_prediction();
		
		// printf("%d\n",start.predict);
		while(!pq.empty()) pq.pop();
		pq.push(start);
		
		set<int> hash;
		while(!pq.empty()) {
			grid top = pq.top(); pq.pop();
			
			int bzz = 0;
			for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
				int val = top.ampas[i][j];
				if (val == 72) val = 10;
				bzz = 13*bzz + val;
			}
			
			if (hash.find(bzz) != hash.end()) continue;
			hash.insert(bzz);
			
			if (top.predict == 0) {
				int size = top.res.size();
				for(int i = 0; i < size; i++) printf("%c",top.res[i]);
				printf("\n");
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
	}
}