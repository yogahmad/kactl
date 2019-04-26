#include<bits/stdc++.h>
using namespace std;

/*
	definisikan BNF :
		Pascal  = Double | Double 'e' Integer | Integer 'e' Integer
		Integer = +Number | -Number | Number
		Double  = Integer | Integer '.' Number
		Number = digit number | digit
*/

bool is_digit(char ch) {
	if (ch >= '0' && ch <= '9') return true;
	return false;
}

bool is_number(string num) {
	if (num.length() == 0) return false; //tidak termasuk notasi, string kosong bukan angka
	if (!is_digit(num[0])) return false;
	if (num.length() == 1) return true; // bagian digit doang -> Number = digit number | DIGIT
	return is_number(num.substr(1)); // bagian rekursif Number = DIGIT NUMBER | digit
}

bool is_integer(string num) {
	if (num.length() == 0) return false;
	if (((num[0] == '-' || num[0] == '+') && is_number(num.substr(1))) || is_number(num)) return true;
	return false;
}

bool is_double(string num) {
	if (num.length() == 0) return false;
	size_t pos = num.find('.');
	if (pos == string::npos) return false;
	if (is_integer(num.substr(0, pos)) && is_number(num.substr(pos+1))) {
		return true;
	} else {
		return false;
	}
}

bool is_pascal(string num) {
	if (num.length() == 0) return false;
	if (is_double(num)) return true;
	size_t pos = num.find('e');
	if (pos == string::npos) return false;
	if (is_double(num.substr(0,pos)) && is_integer(num.substr(pos+1))) return true;
	if (is_integer(num.substr(0,pos)) && is_integer(num.substr(pos+1))) return true;
	return false;
}

string strip(string input) {
	int S, E, sz;
	for (S = 0, sz = input.size(); S < sz; S++) if (input[S] != ' ') break;
	for (E = input.size() - 1; E >= 0; E--) if (input[E] != ' ') break;
	return input.substr(S, E - S + 1);
}

int main() {
	string input;
	while(getline(cin, input)) {
		if (input[0] == '*') break;
		string k = strip(input);
		string s = k;
		for(int i = 0; i < k.length(); i++) if (k[i] == 'E') k[i] = 'e';
		cout << s;
		if (is_pascal(k)) {
			cout << " is legal.";
		} else {
			cout << " is illegal.";
		}
		cout << endl;
	}
	return 0;
}