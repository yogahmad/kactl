#include<bits/stdc++.h>
using namespace std;

struct Polynomials{
	vector<int> coefficient;
	
	void OP(int number) {
		if (coefficient.size() == 0) {
			coefficient.push_back(number);
		} else {
			coefficient[0] += number;
		}
	}
	
	void multiply_by_n() {
		coefficient.push_back(0);
		for(int i = coefficient.size()-1; i >= 1; i--) {
			coefficient[i] = coefficient[i-1];
		}
		coefficient[0] = 0;
	}
	
	void multiply(int number) {
		for(int i = 0; i < coefficient.size(); i++) {
			coefficient[i] *= number;
		}
	}
	
	void combine(Polynomials b) {
		int size_a = coefficient.size();
		int size_b = b.coefficient.size();
		for(int i = 0; i < size_b; i++) {
			if (i >= size_a) coefficient.push_back(b.coefficient[i]);
			else coefficient[i] += b.coefficient[i];
		}
	}
	
	void print() {
		int size = coefficient.size();
		bool all_zero = true;
		for(int i = 0; i < size; i++) if (coefficient[i] != 0) all_zero = false;
		
		if (size == 0 || all_zero) {
			cout << "0\n";
			return;
		}
		
		bool ada = 0;
		for(int i = size-1; i >= 1; i--) {
			if (coefficient[i] == 0) continue;
			if (ada) {
				if (coefficient[i] < 0) cout << "";
				else cout << "+";
			}
			if (coefficient[i] == -1) cout << "-";
			else if (coefficient[i] != 1) cout << coefficient[i] << "*";
			cout << "n";
			if (i != 1) cout << "^" << i;
			ada = true;
		}
		if (coefficient[0] != 0) {
			if (ada) {
				if (coefficient[0] < 0) cout << "";
				else cout << "+";
			}
			cout << coefficient[0];
		} cout << endl;
	}
};

#define MAX 1000005
typedef pair<int,int> command;
#define f first
#define s second
#define mp make_pair
vector<command> perintah;
int bracket[MAX];
/*
	1 = BEGIN    value = -1
	2 = LOOP X   value = X, if (X = n) value = -1
	3 = OP X	 value = X
	0 = END		 value = -1
*/

Polynomials rec(int pos, int l, int r) {
	Polynomials ret;
	
	for(int i = l+1; i < r; i++) {
		if (perintah[i].f == 2) {
			Polynomials x = rec(i, i, bracket[i]);
			if (perintah[i].s == -1) x.multiply_by_n();
			else x.multiply(perintah[i].s);
			ret.combine(x);
			i = bracket[i];
		} else if (perintah[i].f == 3) {
			ret.OP(perintah[i].s);
		}
	}
	
	return ret;
}

int to_integer(string num) {
	int ret = 0;
	int size = num.size();
	for(int i = 0; i < size; i++) {
		ret = 10*ret + (int)(num[i] - '0');
	}
	return ret;
}

int main() {
	int tc;
	scanf("%d",&tc);
	
	for(int program = 1; program <= tc; program++) {	
		perintah.clear();
		string str;
		cin >> str;
		int open = 0;
		if (str == "BEGIN") {
			perintah.push_back(mp(1,-1));
			open = 1;
			while(open != 0) {
				cin >> str;
				if (str == "OP") {
					int number;
					cin >> number;
					perintah.push_back(mp(3,number));
				} else if (str == "LOOP") {
					string tmp;
					cin >> tmp;
					if (tmp == "n") perintah.push_back(mp(2, -1));
					else perintah.push_back(mp(2, to_integer(tmp)));
					open += 1;
				} else if (str == "END") {
					perintah.push_back(mp(0,-1));
					open -= 1;
				}
			}
		}
	
		int size = perintah.size();
		for(int i = 0; i < perintah.size(); i++) {
			bracket[i] = 0;
			if (perintah[i].f == 1) {
				bracket[i] = perintah.size()-1;
			} else if (perintah[i].f == 2) {
				int open = 1;
				for(int j = i+1; j < size; j++) {
					if (perintah[j].f == 0) open--;
					if (perintah[j].f == 2) open++;
					if (open == 0) {
						bracket[i] = j;
						break;
					}
				}
			} 
		}
		
		Polynomials result = rec(0, 0, perintah.size()-1);
		cout << "Program #" << program << endl;
		cout << "Runtime = ";
		result.print();
		cout << endl;
	}
}