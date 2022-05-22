#include <bits/stdc++.h>
using namespace std;

const int N = 112345;

int decrease[N];
int increase[N];

int solve(const auto &v, const auto &limit) {
	for (int i = 0; i < N; i += 1) {
		decrease[i] = 0;
		increase[i] = 0;
	}
	for (int i = 0; i < int(v.size()); i += 1) {
		if (v[i].second == 0) {
			decrease[v[i].first] += 1;
		} else {
			increase[v[i].first] += 1;
		}
	}
	for (int i = 1; i < N; i += 1) {
		decrease[i] += decrease[i - 1];
		increase[i] += increase[i - 1];
	}
	int ans = 0;
	int idx = 0;
	for (int i = N; i >= 0; i -= 1) {
		int current = increase[i] + decrease[N - 1] - ((i > 0) ? decrease[i - 1] : 0);
		if (current >= ans) {
			ans = current;
			idx = i;
		}
	}
	return idx;
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
		// 0 left
		// 1 right
		vector< pair< int, int > > lr;
		// 1 up
		// 0 down
		vector< pair< int, int > > ud;
		for (int i = 0; i < n; i += 1) {
			int x, y;
			char c;
			cin >> x >> y >> c;
			if (c == 'N') {
				ud.push_back({y + 1, 1});
			} else if (c == 'S') {
				ud.push_back({y - 1, 0});
			} else if (c == 'W') {
				lr.push_back({x - 1, 0});
			} else {
				lr.push_back({x + 1, 1});
			}
		}
		cout << "Case #" << test << ": " << solve(lr, q) << ' ' << solve(ud, q) << endl;
	}
	return 0;
}
