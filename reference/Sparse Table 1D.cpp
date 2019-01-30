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