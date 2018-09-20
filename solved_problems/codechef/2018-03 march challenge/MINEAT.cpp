#include <bits/stdc++.h>
using namespace std;
const int N = 112345;

int v[N];

int main () {
	int t; scanf("%d", &t);
	while (t-- > 0) {
		int n, k; scanf("%d %d", &n, &k);
		for (int i = 0; i < n; ++i)
			scanf("%d", &v[i]);
		int lo = 1, hi = 1e9 + 13;
		while (lo <= hi) {
			const int mid = (lo + hi) >> 1;
			int current = 0;
			for (int i = 0; i < n; ++i)
				current += (v[i] + mid - 1) / mid;
			if (current <= k)
				hi = mid - 1;
			else
				lo = mid + 1;
		}
		printf("%d\n", lo);
	}
	return 0;
}