#include<bits/stdc++.h>
using namespace std;
#define MAX 1000005
int n,lps[MAX];
inline int inverse(int x) {return n-1-x;};

string pat;
string text;
string reverse(string x, int a, int b) {
	string ret = "";
	for(int i = b; i >= a; i--) ret += x[i];
	return ret;
}
int KMP(int n, int m) {
	int i = 0, j = 0;
	while(i < n) {
		if (text[i] == pat[j]) {
			i++;
			j++;
		}
		if (i == n) return j;
		if (j == m) {
			j = lps[j - 1];
		} else if (i < n && text[i] != pat[j]) {
			if (j != 0) j = lps[j - 1];
			else i++;
		}
	}
	// printf("%d\n",j);
	return j;
}
void makeLPS(int n) {
	int len = 0, i = 1;
	while(i < n) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i++] = len;
		} else {
			if (len != 0) len = lps[len - 1];
			else lps[i++] = len;
		}
	}
}
int main() {
	while(cin >> text) {
		n = text.length();
		pat = reverse(text, 0, n-1);
		makeLPS(n);		
		cout << text;
		cout << reverse(text, 0, n-KMP(n, n)-1) << endl;
	}
}