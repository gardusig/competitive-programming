#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int degree[N];
vector<int> ans, g[N];

int main () {
	int n, m; scanf("%d %d", &n, &m);
	memset (degree, 0, sizeof degree);
	for (int i = 0; i < n; ++i)
		g[i].clear();
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d %d", &x, &y); --x, --y;
		g[x].push_back(y), ++degree[y];
	}
	queue<int> q;
	for (int i = 0; i < n; ++i)
		if (!degree[i])
			q.push(i);
	ans.clear();
	while (!q.empty()) {
		int i = q.front(); q.pop();
		ans.push_back(i);
		for (int j = 0; j < g[i].size(); ++j)
			if (!(--degree[g[i][j]]))
				q.push(g[i][j]);
	}
	for (int i = 0; i < ans.size(); ++i)
		printf("%d%c", ans[i] + 1, 
			(i == ans.size() - 1) ? '\n' : ' ');
	return 0;
}