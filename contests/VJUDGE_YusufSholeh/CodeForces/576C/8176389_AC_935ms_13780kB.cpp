#include<bits/stdc++.h>
using namespace std;

struct input{
	int x, y, pos;
};

bool cmp(input a, input b) {
	if (a.x/1000 == b.x/1000) {
		if ((a.x/1000)%2 == 0) return a.y < b.y;
		return a.y > b.y;
	}
	return a.x/1000 < b.x/1000;
}

input arr[1000005];
int n;
int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d",&arr[i].x, &arr[i].y);
		arr[i].pos = i;
	}
	
	sort(arr + 1, arr + n + 1, cmp);
	
	for(int i = 1; i <= n; i++) printf("%d ",arr[i].pos);
	
}