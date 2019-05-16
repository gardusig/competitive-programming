#include<bits/stdc++.h>
using namespace std;

const int N = 11;

int dp[N][N][N][N];

int solve(const auto &i, const auto &a, const auto &b, const auto &c) {
	if (i == -1) {
		return 0;
	}
	if (dp[i][a][b][c] != -1) {
		return dp[i][a][b][c];
	}
	int ans = 0;
	if (a - 1 < i and b - 1 < i and c - 1 < i) {
		ans = max(ans, solve(i - 1, a, b, c));
	}
	if (a > 0 and b - 1 < i and c - 1 < i) {
		ans = max(ans, solve(i - 1, a - 1, b, c) + (1 << i));
	}
	if (b > 0 and a - 1 < i and c - 1 < i) {
		ans = max(ans, solve(i - 1, a, b - 1, c) + (1 << i));
	}
	if (c > 0 and a - 1 < i and b - 1 < i) {
		ans = max(ans, solve(i - 1, a, b, c - 1) + (1 << i));
	}
	if (a > 0 and b > 0 and c - 1 < i) {
		ans = max(ans, solve(i - 1, a - 1, b - 1, c));
	}
	if (a > 0 and c > 0 and b - 1 < i) {
		ans = max(ans, solve(i - 1, a - 1, b, c - 1));
	}
	if (b > 0 and c > 0 and a - 1 < i) {
		ans = max(ans, solve(i - 1, a, b - 1, c - 1));
	}
	if (a > 0 and b > 0 and c > 0) {
		ans = max(ans, solve(i - 1, a - 1, b - 1, c - 1) + (1 << i));
	}
	return dp[i][a][b][c] = ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t-- > 0) {
		vector< int > v(3);
		for (int i = 0; i < 3; i += 1) {
			string s;
			cin >> s;
			for (const auto &j: s) {
				v[i] += (j == '1');
			}
		}
		memset(dp, -1, sizeof dp);
		int ans = solve(9, v[0], v[1], v[2]);
		string s = "";
		for (int i = 9; i >= 0; i -= 1) {
			s.push_back((ans & (1 << i)) ? '1' : '0');
		}
		cout << s << endl;
	}
	return 0;
}