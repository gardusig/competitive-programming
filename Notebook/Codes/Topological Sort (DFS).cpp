#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

char used[N];
vector<int> g[N];
stack<int> st, ans;

void dfs (int i, bool flag) {
	used[i] = true;
	for (int k = 0; k < g[i].size(); ++k) {
		int j = g[i][k];
		if (used[j])
			continue;
		dfs(j, flag);
	}
	(flag ? st.push(i) : ans.push(i));
}

int main () {
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d %d", &x, &y); --x, --y;
		g[x].push_back(y);
	}
	memset(used, false, sizeof used);
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs(i, false);
	memset(used, false, sizeof used);
	for (; !st.empty(); st.pop())
		if (!used[st.top()])
			dfs(st.top(), true);
	for (; !ans.empty(); ans.pop())
		printf("%d%c", ans.top() + 1, (ans.size() == 1) ? '\n' : ' ');
	return 0;
}