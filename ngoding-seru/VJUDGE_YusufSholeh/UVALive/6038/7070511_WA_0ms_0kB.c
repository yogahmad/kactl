tc = int(input());
A  = [[0 for j in range(105)] for i in range(105)];
dp = [[0 for i in range(105)] for j in range(105)];

def check(x, y, fx, fy):
	if x < 0 or y < 0 or x >= n or y >= m :
		return False;
	if fx < 0 or fy < 0 or fx >= n or fy >= m :
		return False;
	if A[fx][fy] > A[x][y] :
		return True;
	return False;

def go(x, y):
	if (dp[x][y] != -1):
		return dp[x][y];
		
	dp[x][y] = 0;
	if check(x + 1, y, x, y) :
		dp[x][y] += go(x + 1, y);
	if check(x - 1, y, x, y) :
		dp[x][y] += go(x - 1, y);
	if check(x, y - 1, x, y) :
		dp[x][y] += go(x, y - 1);
	if check(x, y + 1, x, y) :
		dp[x][y] += go(x, y + 1);
	
	dp[x][y] = max(dp[x][y], 1);
	
	return dp[x][y];
	
for case in range(tc):
	n, m = input().split();
	n = int(n)
	m = int(m)
	
	for i in range(n):
		B = input().split();
		for j in range(m):
			A[i][j] = int(B[j]);
			dp[i][j] = -1;
	
	for i in range(n):
		for j in range(m):
			go(i, j);
	
	ans = 0;
	for i in range(n):
		for j in range(m):
			if not (check(i, j, i - 1, j) or check(i, j, i + 1, j) or check(i, j, i, j - 1) or check(i, j, i, j + 1)) :
				ans += dp[i][j];
	
	print("Case #%d: %d\n" % (case + 1, ans));