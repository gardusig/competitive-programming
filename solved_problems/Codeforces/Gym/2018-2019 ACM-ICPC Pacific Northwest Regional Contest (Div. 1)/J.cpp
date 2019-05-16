#include<bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t-- > 0) {
		int n, m;
		cin >> n >> m;
		vector< unordered_map< int, int > > v(n);
		for (int i = 0; i < n; i += 1) {
			for (int j = 0; j < m; j += 1) {
				int x;
				cin >> x;
				v[i][x] += 1;
			}
		}
		int ans = 0;
		for (int i = 1; i < n; i += 1) {
			for (const auto &k: v[i]) {
				int j = k.first;
				ans += min(v[i][j], v[i - 1][j]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}