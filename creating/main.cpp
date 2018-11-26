#include <bits/stdc++.h>
using namespace std;

void optmize_io() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}

void dfs(const auto &i, const auto &p, auto &dp, const auto &g) {
	dp[i] = 0;
	for (const auto &j: g[i]) {
		if (j == p)
			continue;
		dfs(j, i, dp, g);
		dp[i] += dp[j];
	}
	dp[i] = max(dp[i], 1);
}

int main() {
	optmize_io();
	int N; cin >> N;
	vector< vector<int> > g(N);
	for (int i = 1; i < N; ++i) {
		int j; cin >> j; j -= 1;
		g[i].push_back(j);
		g[j].push_back(i);
	}
	vector<int> dp(N);
	dfs(0, -1, dp, g);
	sort(dp.begin(), dp.end());
	for (const auto &i: dp)
		cout << i << ' ';
	return cout << '\n', 0;
}