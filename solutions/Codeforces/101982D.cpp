#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000009;

int K, B;
vector< int > pot;
int dp[129][129][1001];

int solve(const auto &i, const auto &j, const auto &k) {
	if (i == B) {
		return (k == 0) ? j : 0;
	}
	if (dp[i][j][k] != -1) {
		return dp[i][j][k];
	}
	return dp[i][j][k] = (solve(i + 1, j, k) + solve(i + 1, j + 1, (k + pot[i]) % K)) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> K >> B;
	int ans = 0;
	pot.push_back(1);
	for (int i = 1; i < 130; i += 1) {
		pot.push_back((pot[i - 1] << 1) % K);
	}
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0, 0) << endl;
	return 0;
}
