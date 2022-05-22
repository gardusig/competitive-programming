#include <bits/stdc++.h>

class Tree {
public:
	Tree(const int size) {
		N = size;
		g.resize(N);
		dist.resize(N);
		parent.resize(N);
	}

	void add_edge(const int x, const int y) {
		g[x].push_back(y);
		g[y].push_back(x);
	}

	int query() {
		int ans = bfs(bfs(0));
		const int diameter = *std::max_element(dist.begin(), dist.end());
		const int edges = (diameter + 1) >> 1;
		for (int i = 0; i < edges; i += 1) {
			ans = parent[ans];
		}
		return ans;
	}

private:
	int N;
	std::vector<int> dist;
	std::vector<int> parent;
	std::vector<std::vector<int>> g;

	int bfs(const int source) {
		dist = std::vector<int>(N, INT_MAX);
		std::queue<int> q;
		parent[source] = source;
		dist[source] = 0;
		q.push(source);
		int last = -1;
		while (!q.empty()) {
			const int i = q.front();
			q.pop();
			last = i;
			const int nxt = dist[i] + 1;
			for (const int &j : g[i]) {
				if (nxt < dist[j]) {
					parent[j] = i;
					dist[j] = nxt;
					q.push(j);
				}
			}
		}
		return last;
	}
};

int main() {
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);
	std::vector<int> sizes(2);
	for (int &i : sizes) {
		std::cin >> i;
	}
	std::vector<int> ans;
	for (const int &size : sizes) {
		Tree t(size);
		for (int j = 1; j < size; j += 1) {
			int x, y;
			std::cin >> x >> y;
			t.add_edge(x - 1, y - 1);
		}
		ans.push_back(t.query());
	}
	std::cout << ans[0] + 1 << ' ' << ans[1] + 1 << std::endl;
	return 0;
}