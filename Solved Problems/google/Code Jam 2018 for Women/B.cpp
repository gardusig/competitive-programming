#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main () {
	int t; scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		int n; scanf("%d", &n);
		vector< pair<int, ll> > v;
		for (int i = 0; i < n; ++i) {
			ll qtd; int xp; scanf("%lld %d", &qtd, &xp);
			v.push_back(make_pair(xp, qtd));
		}
		sort(v.begin(), v.end());
		ll current = 0, maximum = -1;
		for (int i = 0; i < n; ++i)
			maximum = max(maximum, ll(v[i].first)),
			current = max(0LL, current - (v[i].second * v[i].first)) + v[i].second;
		printf("Case #%d: %lld\n", test, max(current, maximum + 1));
	}
	return 0;
}