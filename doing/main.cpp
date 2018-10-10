#include <bits/stdc++.h>
using namespace std;

long long solve(const int &n, const int &m, const auto &v) {
	vector< vector<int> > dp;
	dp.resize(n);
	for (int i = 0; i < n; ++i)
		dp[i].resize(m);
	long long ans = 0;
	for (int a = 0; a < n; ++a)
		for (int b = 0; b < m; ++b) {
			for (int j = b; j < m; ++j)
				dp[a][j] = 1;
			for (int i = a + 1; i < n; ++i) {
				bool flag = false;
				for (int j = b; j < m; ++j)
					flag |= (v[i][j] != v[a][j]),
					dp[i][j] = dp[i-1][j] + flag;
			}
			for (int i = a; i < n; ++i)
				for (int j = b; j < m; ++j)
					ans += dp[i][j];
		}
	return ans;
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector< vector<int> > v;
	v.resize(n);
	for (int i = 0; i < n; ++i)
		v[i].resize(m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", &v[i][j]);
	return printf("%lld\n", solve(n, m, v)), 0;
}