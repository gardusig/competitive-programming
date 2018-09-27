#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<ll> build (const ll n) {
	vector<ll> ans;
	int limit = sqrt(n) + 2;
	for (ll i = 2, x = n; i <= limit and x > 1; ++i) {
		if (!(x % i))
			ans.push_back(i);
		while (!(x % i) and x > 1)
			x /= i;
		if (i == limit and x > 1)
			ans.push_back(x);
	}	
	return ans;
}

ll solve (const vector<ll> v, const ll n) {
	ll ans = n;
	int limit = (1 << int(v.size()));
	for (int i = 1; i < limit; ++i) {
		ll current = 1;
		for (int j = 0; j < int(v.size()); ++j)
			if ((1 << j) & i)
				current *= v[j];
		ll flag = (__builtin_popcount(i) & 1) ? -1LL : 1LL;
		ans += (flag * n / current);
	}
	return ans;
}

int main () {
	ll n; scanf("%lld", &n);
	if (n == 1)
		return !printf("%lld\n", 2LL);
	vector<ll> factors = build(n);
	return !printf("%lld\n", solve(factors, n));
}