#include<bits/stdc++.h>
using namespace std;

// base and base_digits must be consistent
const int base = 1000000000;
const int base_digits = 9;

struct bigint {
    vector<int> a;
    int sign;

    bigint() :
        sign(1) {
    }

    bigint(long long v) {
        *this = v;
    }

    bigint(const string &s) {
        read(s);
    }

    void operator=(const bigint &v) {
        sign = v.sign;
        a = v.a;
    }

    void operator=(long long v) {
        sign = 1;
        if (v < 0)
            sign = -1, v = -v;
        for (; v > 0; v = v / base)
            a.push_back(v % base);
    }

    bigint operator+(const bigint &v) const {
        if (sign == v.sign) {
            bigint res = v;
            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int) res.a.size())
                    res.a.push_back(0);
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry)
                    res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }

    bigint operator-(const bigint &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                bigint res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                        res.a[i] += base;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }

    void operator+=(const bigint &v) {
        *this = *this + v;
    }
    void operator-=(const bigint &v) {
        *this = *this - v;
    }
	
    bool operator<(const bigint &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator>(const bigint &v) const {
        return v < *this;
    }
    bool operator<=(const bigint &v) const {
        return !(v < *this);
    }
    bool operator>=(const bigint &v) const {
        return !(*this < v);
    }
    bool operator==(const bigint &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const bigint &v) const {
        return *this < v || v < *this;
    }

    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }

    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

	bigint abs() const {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    }
	
    bigint operator-() const {
        bigint res = *this;
        res.sign = -sign;
        return res;
    }

    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--)
            res = res * base + a[i];
        return res * sign;
    }

    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }

    friend istream& operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream &stream, const bigint &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }
	
};

char Sn[10005], Sk[10005];
int tc;
int main() {
	scanf("%d",&tc); getchar();
	while(tc--) {
		scanf("%s %s",&Sn,&Sk);
		int L1 = strlen(Sn);
		int L2 = strlen(Sk);
		bigint N = bigint(Sn);
		bigint K = bigint(Sk);
		bigint dp[105][10][3];
		int lst = (int)Sn[L1 - 1] - '0';
		
		for(int i = 0; i <= L1; i++) {
			for(int j = 0; j < 10; j++) {
				dp[i][j][0] = 0;
				dp[i][j][1] = 0;
				dp[i][j][2] = 0;
			}
		}
		
		for(int i = 0; i < 10; i++) dp[L1 - 1][i][0] = 1;
		dp[L1 - 1][lst][1] = 1;
		if (L1 - 2 >= 0) for(int i = 0; i < 10; i++) dp[L1 - 2][i][2] = 1;
		
		for(int n = L1 - 2; n >= 0; n--) {
			bigint sum = 0;
			bigint sum2 = 0;
			for(int i = 0; i < 10; i++) sum += dp[n + 1][i][0], sum2 += dp[n + 1][i][2];
			for(int i = 0; i < 10; i++) {
				dp[n][i][0] = 1;
				dp[n][i][0] += sum;
				if (n < L1 - 2) {
					dp[n][i][2] = 1;
					dp[n][i][2] += sum2;
				}
			}
			int nw = (int)Sn[n] - '0';
			int nww = (int)Sn[n + 1] - '0';
			dp[n][nw][1] = 1;
			dp[n][nw][1] += dp[n + 1][nww][1];
			for(int i = 0; i < nww; i++) dp[n][nw][1] += dp[n + 1][i][0];
			for(int i = nww + 1; i < 10; i++) dp[n][nw][1] += dp[n + 1][i][2];
		}
		
		
		// for(int i = 0; i < L1; i++) {
			// for(int j = 0; j < 10; j++) {
				// printf("%d %d ",i,j);
				// cout << dp[i][j][0] << " " << dp[i][j][1] << " " << dp[i][j][2] << endl;
			// }
		// }
		
		int kondisi = 1;
		int now = (int)Sn[0] - '0';
		int nw2 = (int)Sk[0] - '0';
		int id = 0;
		bool awal = true;
		bigint res = 0;
		while(id < L2) {
			// printf("%d %d %d\n",id,now,nw2);
			if (kondisi == 1) {
				for(int i = (awal) ? 1 : 0; i < nw2; i++) {
					if (i == now) res += dp[id][i][1];
					else if (i < now) res += dp[id][i][0];
					else res += dp[id][i][2];
				}
				if (nw2 == now) kondisi = 1;
				else if (nw2 > now) kondisi = 2;
				else kondisi = 0;
			} else {
				for(int i = 0; i < nw2; i++) res += dp[id][i][kondisi];
			}
			id++;
			now = (int)Sn[id] - '0';
			nw2 = (int)Sk[id] - '0';
			awal = false;
			// cout << id << " " << res << " " << kondisi << endl;
			res += 1;
		}
		// res += 1;
		cout << res << endl;
	}
}