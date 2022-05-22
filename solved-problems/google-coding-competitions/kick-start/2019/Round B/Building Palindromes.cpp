#include <bits/stdc++.h>
using namespace std;

vector< unordered_map< char, int > > build(const auto &n, const auto &s) {
	vector< unordered_map< char, int > > v(n + 1);
	for (int i = 1; i <= n; i += 1) {
		v[i] = v[i - 1];
		v[i][s[i - 1]] += 1;
	}
	return v;
}

bool valid(const auto &x, const auto &y, auto &v) {
	int odd = 0;
	for (char i = 'A'; i <= 'Z'; i += 1) {
		if ((v[y][i] - v[x - 1][i]) & 1) {
			odd += 1;
		}
	}
	return odd < 2;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int test = 1; test <= t; test += 1) {
		int n, q;
		cin >> n >> q;
		string s;
		cin >> s;
		auto sum = build(n, s);
		int ans = 0;
		while (q-- > 0) {
			int x, y;
			cin >> x >> y;
			if (valid(x, y, sum) == true) {
				ans += 1;
			}
		}
		cout << "Case #" << test << ": " << ans << endl;
	}
	return 0;
}