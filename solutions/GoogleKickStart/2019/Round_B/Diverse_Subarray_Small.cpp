#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int test = 1; test <= t; test += 1) {
		int n, s;
		cin >> n >> s;
		vector< int > v(n);
		for (int i = 0; i < n; i += 1) {
			cin >> v[i];
			v[i] -= 1;
		}
		int ans = 0;
		for (int i = 0; i < n; i += 1) {
			int current = 0;
			unordered_map< int, int > have;
			for (int j = i; j < n; j += 1) {
				if (have[v[j]] < s) {
					current += 1;
					have[v[j]] += 1;
				} else if (have[v[j]] == s) {
					current -= have[v[j]];
					have[v[j]] = INT_MAX;
				}
				ans = max(ans, current);
			}
		}
		cout << "Case #" << test << ": " << ans << endl;
	}
	return 0;
}