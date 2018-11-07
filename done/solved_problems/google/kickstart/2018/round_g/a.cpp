#include <bits/stdc++.h>
using namespace std;

const int N = 212345;

int main () {
	int tests; scanf("%d", &tests);
	for (int test = 1; test <= tests; ++test) {
		int n; scanf("%d", &n);
		vector<int> v(n);
		vector< vector<int> > qtd(N);
		for (int i = 0; i < n; ++i)
			scanf("%d", &v[i]);
		sort(v.begin(), v.end());
		for (int i = 0; i < n; ++i)
			qtd[v[i]].push_back(i);
		long long ans = 0;
		int zeroes = int(qtd[0].size());
		ans += (1LL * (n - zeroes) * zeroes * (zeroes - 1)) / 2;
		ans += (1LL * zeroes * (zeroes - 1) * (zeroes - 2)) / 6;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				long long current = 1LL * v[i] * v[j];
				if (current > 0 and current < N)
					ans += qtd[current].end() - upper_bound(qtd[current].begin(), qtd[current].end(), j);
			}
		printf("Case #%d: %lld\n", test, ans);
	}
	return 0;
}