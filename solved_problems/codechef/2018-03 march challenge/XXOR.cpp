#include <bits/stdc++.h>
using namespace std;
const int N = 112345;
const int M = 31;

int v[N][M], sum[N][M];

int main () {
	int n, q; scanf("%d %d", &n, &q);
	for (int i = 0; i < n; ++i) {
		int x; scanf("%d", &x);
		for (int j = 0; j < M; ++j)
			v[i][j] = (x & (1 << j)) ? 1 : 0;
	}
	for (int j = 0; j < M; ++j)
		sum[0][j] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < M; ++j)
			sum[i][j] = sum[i-1][j] + v[i-1][j];
	while (q-- > 0) {
		int x, y; scanf("%d %d", &x, &y);
		int ans = 0, half = (y - x + 2) >> 1;
		for (int j = 0; j < M; ++j) {
			int qtd = sum[y][j] - sum[x - 1][j];
			if (qtd < half)
				ans += (1 << j);
		}
		printf("%d\n", ans);
	}
	return 0;
}