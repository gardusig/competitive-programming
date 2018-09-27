#include <bits/stdc++.h>
using namespace std;

class edge {
private:
	edge(const auto &to, const auto &flow, const auto &capacity) {
		this->to = to;
		this->flow = flow;
		this->capacity = capacity;
	}
public:
	int to, flow, capacity;
	static void add(const auto &x, const auto &y, const auto &capacity, auto &g, auto &edges) {
		g[x].push_back(int(edges.size())), edges.push_back(edge(y, 0, capacity));
		g[y].push_back(int(edges.size())), edges.push_back(edge(x, 0, 0));
	}
};

class dinic {
private:
	dinic() {}
	static int bfs(const auto &source, const auto &sink, const auto &g, const auto &edges, auto &level) {
		for (int i = 0; i < int(level.size()); ++i)
			level[i] = INT_MAX;
		queue<int> q;
		level[source] = 0, q.push(source);
		while (!q.empty()) {
			int i = q.front(); q.pop();
			for (const int& j : g[i])
				if (level[edges[j].to] > level[i] + 1 and edges[j].flow < edges[j].capacity)
					level[edges[j].to] = level[i] + 1, q.push(edges[j].to);
		}
		return level[sink] < INT_MAX;
	}
	static int dfs(const auto &i, const auto &sink, const auto &flow, const auto &g, auto &edges, const auto &level, auto &start) {
		if (i == sink)
			return flow;
		while (start[i] < int(g[i].size())) {
			int j = g[i][start[i]++];
			if (level[edges[j].to] == level[i] + 1 and edges[j].flow < edges[j].capacity)
				if (int nxt = dfs(edges[j].to, sink, min(flow, edges[j].capacity - edges[j].flow), g, edges, level, start)) {
					edges[j].flow += nxt, edges[j ^ 1].flow -= nxt;
					return nxt;
				}
		}
		return 0;
	}
public:
	static int solve(const auto &source, const auto &sink, const auto &g, auto &edges, auto &level, auto &start) {
		int ans = 0;
		while (bfs(source, sink, g, edges, level)) {
			for (int i = 0; i < int(start.size()); ++i)
				start[i] = 0;
			while (int i = dfs(source, sink, INT_MAX, g, edges, level, start))
				ans += i;
		}
		return ans;
	}
};

int solve(const auto &gas_stations, const auto &refineries, const auto &v) {
	int vertexes = 0;
	int source = vertexes++;
	int sink = vertexes++;
	int total = accumulate(gas_stations.begin(), gas_stations.end(), 0);
	vector<int> convert_refineries(int(refineries.size()));
	for (int i = 0; i < int(refineries.size()); ++i)
		convert_refineries[i] = vertexes++;
	vector<int> convert_gas_stations(int(gas_stations.size()));
	for (int i = 0; i < int(gas_stations.size()); ++i)
		convert_gas_stations[i] = vertexes++;
	vector<edge> edges;
	vector< vector<int> > g(vertexes);
	vector<int> level(vertexes), start(vertexes);
	int ans = -1, lo = 0, hi = int(v.size()) - 1;
	while (lo <= hi) {
		const int mid = lo + ((hi - lo) >> 1);
		edges.clear();
		for (int i = 0; i < int(g.size()); ++i)
			g[i].clear();
		for (int i = 0; i < int(refineries.size()); ++i)
			edge::add(source, convert_refineries[i], refineries[i], g, edges);
		for (int i = 0; i < int(gas_stations.size()); ++i)
			edge::add(convert_gas_stations[i], sink, gas_stations[i], g, edges);
		for (int i = 0; i <= mid; ++i) {
			int x = convert_refineries[v[i].second.first];
			int y = convert_gas_stations[v[i].second.second];
			edge::add(x, y, INT_MAX, g, edges);
		}
		int current = dinic::solve(source, sink, g, edges, level, start);
		if (current == total)
			ans = v[mid].first,
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return ans;
}

int main() {
	int p, r, c; scanf("%d %d %d", &p, &r, &c);
	vector<int> gas_stations(p);
	for (int i = 0; i < p; ++i)
		scanf("%d", &gas_stations[i]);
	vector<int> refineries(r);
	for (int i = 0; i < r; ++i)
		scanf("%d", &refineries[i]);
	vector< pair<int, pair<int, int> > > v;
	for (int i = 0; i < c; ++i) {
		int x, y, t; scanf("%d %d %d", &x, &y, &t), --x, --y;
		v.push_back({t, {y, x}});
	}
	sort(v.begin(), v.end());
	return printf("%d\n", solve(gas_stations, refineries, v)), 0;
}