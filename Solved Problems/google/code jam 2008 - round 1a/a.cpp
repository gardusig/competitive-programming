#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<int> a, b;

int main () {
	int t; scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		int n; scanf("%d", &n);
		a.clear(), b.clear();
		for (int i = 0; i < n; ++i) {
			int x; scanf("%d", &x);
			a.push_back(x);
		}
		for (int i = 0; i < n; ++i) {
			int x; scanf("%d", &x);
			b.push_back(x);
		}
		ll ans = 0;
		sort(a.begin(), a.end());
		sort(b.rbegin(), b.rend());
		for (int i = 0; i < n; ++i)
			ans += ll(a[i]) * ll(b[i]);
		printf("Case #%d: %lld\n", test, ans);
	}
	return 0;
}