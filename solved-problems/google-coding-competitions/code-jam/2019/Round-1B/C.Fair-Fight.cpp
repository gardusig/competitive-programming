#include <bits/stdc++.h>
using namespace std;

const int N = 1123;

int kappa[N][N];
int keepo[N][N];

void build(const auto &c, const auto &d) {
	for (int i = 0; i < int(c.size()); i += 1) {
		kappa[i][i] = c[i];
		for (int j = i + 1; j < int(c.size()); j += 1) {
			kappa[i][j] = max(kappa[i][j - 1], c[j]);
		}
	}
	for (int i = 0; i < int(d.size()); i += 1) {
		keepo[i][i] = d[i];
		for (int j = i + 1; j < int(d.size()); j += 1) {
			keepo[i][j] = max(keepo[i][j - 1], d[j]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int test = 1; test <= t; test += 1) {
		int n, k;
		cin >> n >> k;
		vector< int > c(n);
		vector< int > d(n);
		for (int i = 0; i < n; i += 1) {
			cin >> c[i];
		}
		for (int i = 0; i < n; i += 1) {
			cin >> d[i];
		}
		build(c, d);
		int ans = 0;
		for (int i = 0; i < n; i += 1) {
			for (int j = i; j < n; j += 1) {
				if (abs(kappa[i][j] - keepo[i][j]) <= k) {
					ans += 1;
				}
			}
		}
		cout << "Case #" << test << ": " << ans << endl;
	}
	return 0;
}