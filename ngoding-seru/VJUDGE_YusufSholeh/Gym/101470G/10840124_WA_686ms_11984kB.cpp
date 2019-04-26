#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define LL long long

const int MAXL = 1002;

int n;

int refer[MAXL];
int mask;
char rev[MAXL];

int dp[MAXL][MAXL];
string nonT[MAXL];

int dp_mask[MAXL][MAXL];
int ada[MAXL][MAXL];

int gabung(int mask1, int mask2) {

    if (dp_mask[mask1][mask2] != -1) return dp_mask[mask1][mask2];

    int new_mask = 0;
    for(int i = 0; i < mask; i++) {
        for(int j = 0; j < mask; j++) {
            if ( ((1 << i) & mask1) && ((1 << j) & mask2) && (ada[i][j] != -1)) {
                new_mask |= (1 << ada[i][j]);
            }
        }
    }

    return dp_mask[mask1][mask2] = new_mask;
}

int main(){
    freopen("g.in", "r", stdin);
    string x;
    cin >> x;

    n = x.length();

    x = '$' + x;

    int ptr = 0;
    string k;

    memset(ada, -1, sizeof ada);
    memset(refer,-1,sizeof(refer));
    while(cin >> k) {
        for(int i = 0; i < k.length(); i++) {
            if (isupper(k[i]) && refer[k[i]] == -1) {
                rev[mask] = k[i];
                refer[k[i]] = mask++;
            }
        }
        if (k.length() == 2) {
            for(int i = 1; i <= n; i++) {
                if (x[i] == k[1]) {
                    dp[i][i] |= (1 << refer[k[0]]);
                }
            }
        } else {
            ++ptr;
            nonT[ptr] = k;
            ada[refer[k[1]]][refer[k[2]]] |= refer[k[0]];
            // printf("%d\n",ada[0][0]);
            // printf("%d\n",refer[k[0]]);
        }
    }

    memset(dp_mask, -1, sizeof dp_mask);


    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= n - i + 1; j++) {
            for(int k = 1; k < i; k++) {
                dp[j][j+i-1] |= gabung(dp[j][j+k-1], dp[j+k][j+i-1]);
            }
        }
    }    

    int ret = dp[1][n];
    int val = refer['S'];

    if (ret & (1 << val)) printf("1\n");
    else printf("0\n");
}