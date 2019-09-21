#include<bits/stdc++.h>
#define MAX 100005
#define f first
#define s second
using namespace std;
int tc, n, a, b;
int arr[MAX], suf[MAX], zero[MAX], id[MAX];
int neg[MAX];
typedef pair<int,int> pii;
pii inp[MAX];
int main() {
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%d %d %d",&n,&a,&b);
		for(int i = 1; i <= n; i++) scanf("%d",&inp[i].f), inp[i].s = i;
		sort(inp + 1, inp + n + 1);
		for(int i = 1; i <= n; i++) arr[i] = inp[i].f, id[i] = inp[i].s;
		int last = -1;
		int ada = -1;
		int las = -1;
		for(int i = n; i >= 1; i--) {
			suf[i] = (abs(arr[i]) == 2) + suf[i + 1];
			zero[i] = (arr[i] == 0) + zero[i + 1];
			neg[i] = (arr[i] < 0) + neg[i + 1];
			if (arr[i] == 0) ada = i;
			if (last == -1) last = (zero[i]) ? i + 1 : last;
			if (las == -1) las = (arr[i] <= 0) ? i + 1 : las;
		}
		for(int i = 1; i <= n; i++) {
			if (neg[i] % 2 == 0) neg[i] = 1;
			else neg[i] = -1;
		}
		neg[n + 1] = 1;
		int mak = -MAX, pos = -1, cur = 0, plus = 2, posr = n + 1, mak2 = -MAX;
		arr[0] = -3;
		for(int i = 0; i <= n; i++) {
			if (arr[i] == -2) cur += 1,plus = 2 - plus;
			else if (arr[i] == -1) plus = 2 - plus;
			else if (arr[i] ==  2) cur += 1;
			if (i > b) break;
			//ambil b - i dari belakang
			int idx = n - (b - i) + 1;
			int tambah = suf[idx]; 
			int ri = b - i;
			if (zero[idx]) {
				tambah = suf[last];
				ri = n - last + 1;
				idx = last;
			}
			// printf("%d %d %d\n",i,ri,last);
			// printf("%d %d %d %d\n",plus,cur,tambah,idx);
			
			int parit = (plus - 1)*neg[idx];
			int val = (tambah + cur)*parit;
			
			if (i + ri >= a && i + ri <= b && (val > mak || (val == mak && parit > mak2))) {
				mak = val;
				mak2 = parit;
				pos = i, posr = idx;
				// printf("mak %d %d %d %d\n",mak,pos,posr,neg[idx]);
			}
			if (idx <= las) {
				tambah = suf[las];
				ri = n - las + 1;
				idx = las;
				
				parit = (plus - 1)*neg[idx];
				val = (tambah + cur)*parit;
				
				if (i + ri >= a && i + ri <= b && (val > mak || (val == mak && parit > mak2))) {
					mak = val;
					mak2 = parit;
					pos = i, posr = idx;
					// printf("mak2 %d %d %d %d %d %d\n",mak,pos,posr,neg[idx],las,ri);
				}
			}
		}
		printf("Case #%d:\n",cs); //printf("%d %d\n",mak,ada);
		if (ada > 0 && (mak < 0 || (mak == 0 && mak2 < 0))) {
			int rem = a - 1;
			printf("%d\n",a);
			printf("%d",id[ada]);
			for(int i = 1; i <= n; i++) {
				if (rem == 0) break;
				if (id[i] == id[ada]) continue;
				printf(" %d",id[i]); --rem;
			}
		} else {
			printf("%d\n",pos + (n - posr + 1));
			bool first = true;
			for(int i = 1; i <= pos; i++) {
				if (first) printf("%d",id[i]), first = false;
				else printf(" %d",id[i]);
			}
			for(int i = n; i >= posr; i--) {
				if (first) printf("%d",id[i]), first = false;
				else printf(" %d",id[i]);
			}
		}
		printf("\n");
		for(int i = 0; i < MAX; i++) neg[i] = zero[i] = suf[i] = id[i] = arr[i] = inp[i].f = inp[i].s = 0;
	}
}