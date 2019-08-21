#include <bits/stdc++.h>
using namespace std;

const int N = 1123;

int dp[N][N];
int k;
string a;
string b;

int solve(const auto &i, const auto &j) {
	if (dp[i][j] != -1) {
		return dp[i][j];
	}
	if (i == int(a.size())) {
		return dp[i][j] = (j == k) ? 0 : INT_MIN;
	}
	int ans = solve(i + 1, j) + (a[i] != b[i]);
	if (j < k) {
		ans = max(ans, solve(i + 1, j + 1) + (a[i] == b[i]));
	}
	return dp[i][j] = ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> k >> a >> b;
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << endl;
	return 0;
}
