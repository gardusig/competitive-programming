#include <bits/stdc++.h>
using namespace std;
const int N = 112;

int main () {
	int v[N];
	int t; scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		int n; scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &v[i]);
		sort(v, v + n);
		int ans = 0;
		for (int i = 0, j = 0; i < n; ++i) {
			ans += (v[i] - j) * (v[i] - j);
			if (i & 1)
				++j;
		}
		printf("Case #%d: %d\n", test, ans);
	}
	return 0;
}