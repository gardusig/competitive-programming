#include <bits/stdc++.h>
using namespace std;

const int N = 1000000 + 5;

vector< int > build_primes(auto &v) {
	vector< int > ans;
	for (int i = 2; i < N; i += 1) {
		if (v[i] == true) {
			ans.push_back(i);
			for (int j = i + i; j < N; j += i) {
				v[j] = false;
			}
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	vector< bool > v(N, true);
	auto primes = build_primes(v);
	int n;
	cin >> n;
	int ans = 0;
	while (n >= 4) {
		ans += 1;
		for (int i = 1; true; i += 1) {
			if (v[n - primes[i]] == true) {
				n -= (primes[i] + primes[i]);
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
