#include<bits/stdc++.h>
using namespace std;

int solve(const auto &n, const auto &k, const auto &MOD) {
	if (k == 0) {
		return 1;
	}
	int ans = solve(n, k >> 1, MOD);
	ans = (1LL * ans * ans) % MOD;
	if (k & 1) {
		ans = (1LL * ans * n) % MOD;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t-- > 0) {
		int n, m;
		cin >> n >> m;
		for (int i = 12; i > 1; i -= 10) {
			int kappa = (0LL + solve(5, n, i) + solve(7, n, i)) % i;
			int keepo = (0LL + solve(5, m, i) + solve(7, m, i)) % i;
			if (kappa == 0 and keepo == 0) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}