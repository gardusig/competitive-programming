#include <bits/stdc++.h>
using namespace std;

vector< vector< int > > build_sparse_table(const auto &v) {
	int n = int(v.size());
	int m = log2(n) + 5;
	vector< vector< int > > st(n);
	for (int i = 0; i < n; ++i)
		st[i] = vector< int >(m);
	for (int i = 0; i < n; ++i)
		st[i][0] = v[i];
	for (int j = 1; j < m; ++j)
		for (int i = 0; i + (1 << j) <= n; ++i)
			st[i][j] = max(st[i][j-1], st[i + (1 << (j - 1))][j-1]);
	return st;
}

int query_sparse_table(const auto &x, const auto &y, const auto &st) {
	int dist = y - x + 1;
	int z = 31 - __builtin_clz(dist);
	return max(st[x][z], st[x + dist - (1 << z)][z]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int mx = 0;
	int n; cin >> n;
	vector< int > v(n);
	for (int i = 0; i < n; i += 1)
		cin >> v[i],
		mx = max(mx, v[i]);
	auto st = build_sparse_table(v);
	for (int i = 0; i < n;) {
		if (v[i] == mx) {
			i += 1;
			continue;
		}
		int lo = i, hi = n - 1;
		while (lo <= hi) {
			const int mid = lo + ((hi - lo) >> 1);
			if (query_sparse_table(i, mid, st) > v[i])
				hi = mid - 1;
			else
				lo = mid + 1;
		}
		int l = i, r = lo - 1;
		if ((r - l + 1) & 1)
			return cout << "NO" << '\n', 0;
		i = lo;
	}
	return cout << "YES" << '\n', 0;
}