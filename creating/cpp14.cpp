#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 512345;

void optmize_io() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}

vector< int > build_divisors(const auto &n) {
	vector< int > v(n);
	for (int i = 0; i < n; ++i)
		v[i] = i;
	for (int i = 2; i < n; ++i)
		if (v[i] == i)
			for (int j = i + i; j < n; j += i)
				if (v[j] == j)
					v[j] = i;
	return v;
}

vector< int > factorize(const auto &n, const auto &div) {
	vector< int > ans;
	for (int i = n; i > 1; i /= div[i])
		ans.push_back(div[i]);
	set< int > s(ans.begin(), ans.end());
	ans.assign(s.begin(), s.end());
	return ans;
}

int main() {
	optmize_io();
	int n, t; cin >> n >> t;
	auto divisors = build_divisors(MAX_SIZE);
	vector< vector< int > > factors(n);
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		factors[i] = factorize(x, divisors);
	}
	int size = 0;
	long long ans = 0;
	vector< bool > stock(n, false);
	vector< int > have(MAX_SIZE, 0);
	while (t-- > 0) {
		int x; cin >> x; x -= 1;
		if (stock[x] == true)
			for (const auto &i: factors[x])
				have[i] -= 1;
		int incompatible = 0;
		for (int mask = 1; mask < (1 << int(factors[x].size())); mask += 1) {
			int current = 1, qtd = 0;
			for (int pos = 0; pos < int(factors[x].size()); pos += 1)
				if (mask & (1 << pos))
					qtd += 1,
					current *= factors[x][pos];
			incompatible += ((qtd & 1) ? +1 : -1) * have[current];
		}
		if (stock[x] == true) {
			ans -= (size - 1 - incompatible),
			size -= 1;
		}
		else {
			ans += (size - incompatible),
			size += 1;
			for (const auto &i: factors[x])
				have[i] += 1;
		}
		stock[x] = !stock[x];
		cout << ans << '\n';
	}
	return 0;
}