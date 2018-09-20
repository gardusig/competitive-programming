#include <bits/stdc++.h>
using namespace std;

map<int, int> v;

int main () {
	int t; scanf("%d", &t);
	while (t-- > 0) {
		int n; scanf("%d", &n);
		v.clear();
		for (int i = 0; i < n; ++i) {
			int x; scanf("%d", &x);
			++v[x];
		}
		int ans = 0;
		for (auto i : v)
			ans += (i.second - 1);
		printf("%d\n", ans);
	}
	return 0;
}