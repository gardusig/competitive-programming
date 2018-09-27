#include <bits/stdc++.h>
using namespace std;

void build(auto &dp) {
	const int N = 112;
	vector< vector<bool> > win(N);
	for (int i = 0; i < N; ++i)
		win[i] = vector<bool>(N, false);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (!win[i][j])
				for (int k = 1; k < N; ++k) {
					if (i + k < N)
						win[i + k][j] = true;
					if (j + k < N)
						win[i][j + k] = true;
					if (i + k < N and j + k < N)
						win[i + k][j + k] = true;
				}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j)
			cout << win[i][j] << " ";
		puts("");
	}
	dp.resize(N);
	for (int i = 0; i < N; ++i)
		dp[i] = vector<int>(N);
	for (int i = 1; i < N; ++i)
		for (int j = 1; j < N; ++j)
			for (int k = 1; k < N; ++k) {
				int current = 0;
				if (i - k >= 0)
					current |= (1 << win[i - k][j]);
				if (j - k >= 0)
					current |= (1 << win[i][j - k]);
				if (i - k >= 0 and j - k >= 0)
					current |= (1 << win[i - k][j - k]);
				for (int l = 0; l < 3; ++l)
					if (!(current & (1 << l))) {
						dp[i][j] = l;
						break;
					}
			}
}

int main() {
	vector< vector<int> > dp;
	build(dp);
	int n; scanf("%d", &n);
	int ans = 0;
	while (n-- > 0) {
		int x, y; scanf("%d %d", &x, &y);
		if (x == y)
			return printf("%s\n", "Y"), 0;
		else
			ans ^= dp[x][y];
	}
	return printf("%s\n", (ans > 0) ? "Y" : "N"), 0;
}