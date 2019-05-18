#include<bits/stdc++.h>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while (t-- > 0) {
		int n, m, q;
		scanf("%d %d %d", &n, &m, &q);
		vector< bool > v(m + 5, false);
		while (n-- > 0) {
			int x, y;
			scanf("%d %d", &x, &y);
			for (int i = x; i <= y; i += 1) {
				v[i] = true;
			}
		}
		int current = 0;
		vector< int > dp(m + 5, -1);
		for (int i = 1; i <= m; i += 1) {
			if (v[i] == false) {
				current += 1;
			} else {
				current = 0;
			}
			dp[current] = i;
		}
		for (int i = m - 1; i > 0; i -= 1) {
			dp[i] = max(dp[i], dp[i + 1]);
		}
		while (q-- > 0) {
			int k;
			scanf("%d", &k);
			printf("%d %d\n", max(-1, dp[k] - k + 1), dp[k]);
		}
	}
	return 0;
}