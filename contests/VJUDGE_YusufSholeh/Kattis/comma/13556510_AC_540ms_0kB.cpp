#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 5;

typedef pair<int, int> pii;
#define mp make_pair
#define f first
#define s second

typedef pair<long long, long long> pll;

vector<string> sentence[MAX];
vector<int> scpy[MAX];
map<pair<pll, bool> , long long> done;
map<pll, vector<pii> > pos;


typedef pair<string, bool> psb;
queue<psb> q;

const long long MOD = 1e9 + 7;
const long long MOD3 = 1e9 + 9;

long long res,res3;

pll HASH(string str) {
	res = 1;
	res3 = 1;
	for(int i = 0; i < (int)str.length(); i++) {
		int nilai = (int)(str[i] - 'a' + 1);
		res = (res * 37 + nilai);
		res %= MOD;

		res3 = (res3 * 41 + nilai);
		res3 %= MOD3;
	}
	return mp(res, res3);
}

int main() {
	ios_base::sync_with_stdio( false ); cin.tie(NULL);

	int kalimat = 0;
	string str;

	bool sebelum = false;
	while(cin >> str) {
		if (sebelum) {
			string tmp = str;
			if (tmp.back() == ',' || tmp.back() == '.') tmp.pop_back();
			q.push(make_pair(tmp, false));
			sebelum = false;
		}
		if (str.back() == ',') {
			str.pop_back();
			q.push(make_pair(str, true));
			sebelum = true;
			pos[HASH(str)].push_back(make_pair(kalimat, sentence[kalimat].size()));
			sentence[kalimat].push_back(str);
			scpy[kalimat].push_back(1);
		} else if (str.back() == '.') {
			str.pop_back();
			pos[HASH(str)].push_back(make_pair(kalimat, sentence[kalimat].size()));
			sentence[kalimat].push_back(str);
			scpy[kalimat].push_back(2);
			kalimat++;
		} else {
			pos[HASH(str)].push_back(make_pair(kalimat, sentence[kalimat].size()));
			sentence[kalimat].push_back(str);
			scpy[kalimat].push_back(0);
		}
	}

	/*for(int i = 0; i < kalimat; i++) {
		for(string word : sentence[i]) {
			cout << word << " ";
		}
		cout << endl;
	}

	for(int i = 0; i < kalimat; i++) {
		for(int word : scpy[i]) {
			cout << word << " ";
		}
		cout << endl;
	}
	*/	

	while(!q.empty()) {
		pair<string, bool> top = q.front();
		q.pop();


		string now = top.first;
		pll val = HASH(now);
		bool belakang = top.second;
		if (done.count(mp(val,belakang))) continue;
		done[mp(val, belakang)] = 1;

		// cout << top.first << " " << top.second << endl;

		vector<pii> V = pos[val];
		
		for(pii cur : V) {
			if (belakang) {
				if (cur.second != (int)scpy[cur.first].size()-1) {
					scpy[cur.first][cur.second] = 1;
					q.push(make_pair(sentence[cur.first][cur.second + 1], false));
				}
			} else {
				if (cur.second != 0) {
					scpy[cur.first][cur.second-1] = 1;
					q.push(make_pair(sentence[cur.first][cur.second - 1], true));
				}
			}
		}

		/*
		for(int i = 0; i < kalimat; i++) {
			for(int j = 0; j < (int)sentence[i].size(); j++) {
				if (!(i == 0 && j == 0)) cout << " ";
				if (scpy[i][j] == 0) {
					cout << sentence[i][j];
				} else if (scpy[i][j] == 1) {
					cout << sentence[i][j] << ",";
				} else {
					cout << sentence[i][j] << '.';
				}
			}
		}
		cout << endl;
		*/
	}

	for(int i = 0; i < kalimat; i++) {
		for(int j = 0; j < (int)sentence[i].size(); j++) {
			if (!(i == 0 && j == 0)) cout << " ";
			if (scpy[i][j] == 0) {
				cout << sentence[i][j];
			} else if (scpy[i][j] == 1) {
				cout << sentence[i][j] << ",";
			} else {
				cout << sentence[i][j] << '.';
			}
		}
	}
	cout << endl;

  return 0;
}