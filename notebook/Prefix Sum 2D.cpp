#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;

int n, m;
int v[N][N], sum[N][N];

void build () {
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			sum[i][j] = 0;
			if (!i or !j)
				continue;
			sum[i][j] += sum[i - 1][j];
			sum[i][j] += sum[i][j - 1];
			sum[i][j] += v[i - 1][j - 1];
			sum[i][j] -= sum[i - 1][j - 1];
		}
	}
}

int query (const int x0, const int y0, const int x1, const int y1) {
	int ans = 0;
	ans += sum[x1][y1];
	ans -= sum[x1][y0 - 1];
	ans -= sum[x0 - 1][y1];
	ans += sum[x0 - 1][y0 - 1];
	return ans;
}

int main () {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", &v[i][j]);
	build();
	int q; scanf("%d", &q);
	while (q-- > 0) {
		int x0, y0, x1, y1; scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
		printf("%d\n", query(x0, y0, x1, y1));
	}
	return 0;
}