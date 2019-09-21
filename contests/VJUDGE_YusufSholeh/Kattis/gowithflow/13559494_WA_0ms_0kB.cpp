#include <bits/stdc++.h>
using namespace std;

const int N = 2505;
const int DUA = 2e5 + 1;

int n;
string arr[N];

int ptr, ptr2, col, col2, row, row2;
int dp[N];

void maju(int &ptr, int &row, int &col, int ukuran_colom) {
	if (col + (int)arr[ptr].length() + (int)arr[ptr+1].length() >= ukuran_colom) {
		row += 1;
		col = 0;
		ptr += 1;
	} else {
		col += (int)arr[ptr].length() + 1;
		ptr += 1;
	}
}

int main() {
	cin >> n;
	int maxx = 0;
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
		// cout << arr[i] << endl;
		maxx = max(maxx, (int)arr[i].length());
	}

	int col_ans = 0;
	int ans = 0;

	for(int i = maxx; i <= DUA; i++) {
		int current_ans = 0;
		memset(dp, 0, sizeof dp);
		ptr = ptr2 = 0;
		col = col2 = 0;
		row = row2 = 0;	

		while(ptr < n) {
			// printf("Zats %d %d %d %s\n", ptr, row, col, arr[ptr].c_str());
			// printf("Zbwh %d %d %d %s\n", ptr2, row2, col2, arr[ptr2].c_str());

			while(row2 == row) {
				maju(ptr2, row2, col2, i);
				// printf("maju %d %d %d %s\n",row2, col2, ptr2, arr[ptr2].c_str());
				if (ptr2 == n) break;
			}
			// printf("gg ats %d %d %d\n", ptr, row, col);
			// printf("bwh %d %d %d\n", ptr2, row2, col2);
			while(row2 == row + 1 && col2 + (int)arr[ptr2].length() <= col - 2 + (int)arr[ptr].length()) {
				maju(ptr2, row2, col2, i);
				if (ptr2 == n) break;
			}
			if (ptr2 == n) break;

			if (row + 2 == row2) {
				maju(ptr, row, col, i);
				// printf("gg coy\n");
				continue;
			}

			if (ptr2 >= n) break;

			// printf("ats %d %d %d %s\n", ptr, row, col, arr[ptr].c_str());
			// printf("bwh %d %d %d %s\n", ptr2, row2, col2, arr[ptr2].c_str());

			if (row2 == row + 1 && abs(col + (int)arr[ptr].length() - (col2 + (int)arr[ptr2].length())) <= 1) {
				int satu_ptr = ptr;
				int satu_row = row;
				int satu_col = col;
				int dua_ptr2 = ptr2;
				int dua_row2 = row2;
				int dua_col2 = col2;
				maju(satu_ptr, satu_row, satu_col, i);
				maju(dua_ptr2, dua_row2, dua_col2, i);

				// printf("msk\n");
				// cout << arr[ptr] << " " << arr[ptr2] << endl;
				if (dua_ptr2 == n || satu_row != row || dua_row2 != row2) {

				} else {
					// printf("jadi\n");
					dp[ptr2] = max(dp[ptr2], dp[ptr] + 1);
					current_ans = max(current_ans, dp[ptr2]);
				}
			}

			int dua_ptr2 = ptr2;
			int dua_row2 = row2;
			int dua_col2 = col2;			

			if (ptr2 >= n) break;

			maju(dua_ptr2, dua_row2, dua_col2, i);
			if (dua_row2 == row2 && ((dua_col2 + (int)arr[dua_ptr2].length()) - (col2 + (int)arr[ptr2].length()) == 2)) {
				maju(ptr2, row2, col2, i);	
				//  printf("gg\n");
			} else {
				maju(ptr, row, col, i);
				// printf("wtf\n");
			}
		}

		if (current_ans > ans) {
			ans = current_ans;
			col_ans = i;
		}
	}

	cout << col_ans << " " << ans+1 << endl;
}