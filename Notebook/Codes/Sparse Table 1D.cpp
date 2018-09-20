const int N = 212345;
const int M = log2(N) + 5;

int n, q;
int st[N][M], v[N];

void build_sparse_table() {
	for (int i = 0; i < n; ++i)
		st[i][0] = v[i];
	for (int j = 1; j < M; ++j)
		for (int i = 0; i + (1 << j) < N; ++i)
			st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j-1]);
}

int query_sparse_table(const int &x, const int &y) {
	int dist = y - x + 1;
	int z = 31 - __builtin_clz(dist);
	return min(st[x][z], st[x + dist - (1 << z)][z]);
}