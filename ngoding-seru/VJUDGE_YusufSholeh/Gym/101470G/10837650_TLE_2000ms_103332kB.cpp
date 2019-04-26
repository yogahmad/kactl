#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define LL long long

const int MAXL = 1002;

bool P[MAXL][MAXL][105];

string terminal[105];
string nonterminal[105];

int getR(char X) {
    if (X == 'S') return 1;
    if (X < 'S') {
        return X - 'A' + 2;
    } else {
        return X - 'A' + 1;
    }
}


// A = 1  -> A : 2
// R = 18 -> R : 19
// S = 19 -> S : 20
// T = 20 -> T : 20
// P Q R S T 
//

int main(){
    freopen("g.in", "r", stdin);
    string a;
    cin >> a;
    int n = a.length();
    a = '$' + a;

    int r = 0;
    int nr = 0;
    string k;
    while(cin >> k) {
        if (k.length() == 2) {
            r += 1;
            terminal[r] = k;
        } else {
            nr += 1;
            nonterminal[nr] = k;
        }
    }

    assert(r <= 50 && nr <= 50);

    for(int s = 1; s <= n; s++) {
        for(int v = 1; v <= r; v++) {
            int newv = getR(terminal[v][0]);
            if (terminal[v][1] == a[s]) {
                P[1][s][newv] = true;
            }
        }
    }

    for(int l = 2; l <= n; l++) {
        for(int s = 1; s <= n-l+1; s++) {
            for(int p = 1; p <= l-1; p++) {
                for(int i = 1; i <= nr; i++) {
                    int Rb = getR(nonterminal[i][1]);
                    int Rc = getR(nonterminal[i][2]);
                    if (P[p][s][Rb] && P[l-p][s+p][Rc]) {
                        int Ra = getR(nonterminal[i][0]);
                        P[l][s][Ra] = true;
                    }
                }
            }
        }
    }

    if (P[n][1][1]) {
        printf("1\n");
    } else {
        printf("0\n");
    }
}