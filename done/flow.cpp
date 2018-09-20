#include <bits/stdc++.h>
using namespace std;

const int N = 712;

class edge {
private:
	edge(const int& to, const int& flow, const int& capacity) {
		this->to = to, this->flow = flow, this->capacity = capacity;
	}
public:
	int to, flow, capacity;
	static void add(const int& x, const int& y, const int& capacity, vector< vector<int> >& g, vector<edge>& edges) {
		g[x].push_back(int(edges.size())), edges.push_back(edge(y, 0, capacity));
		g[y].push_back(int(edges.size())), edges.push_back(edge(x, 0, 0));
	}
};

class ford_fulkerson {
//~ complexity: (max_flow * edges)
private:
	ford_fulkerson() {}
	static int dfs(const int& i, const int& flow, const int& sink, const vector< vector<int> >& g, vector<edge>& edges, vector<int>& seen, int& current) {
		if (i == sink)
			return flow;
		seen[i] = current;
		for (const int& j : g[i])
			if (seen[edges[j].to] < current and edges[j].flow < edges[j].capacity)
				if (int nxt = dfs(edges[j].to, min(flow, edges[j].capacity - edges[j].flow), sink, g, edges, seen, current)) {
					edges[j].flow += nxt, edges[j ^ 1].flow -= nxt;
					return nxt;
				}
		return 0;
	}
public:
	static int solve(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges) {
		vector<int> seen(N, 0);
		int ans = 0, current = 0;
		while (int i = dfs(source, INT_MAX, sink, g, edges, seen, ++current))
			ans += i;
		return ans;
	}
};

class edmonds_karp {
//~ complexity: (vertexes * edges * edges)
private:
	edmonds_karp() {}
	static int bfs(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges, vector<int>& seen, vector<int>& parent, int& current) {
		queue< pair<int, int> > q;
		seen[source] = current;
		q.push({source, -1});
		while (!q.empty()) {
			int i = q.front().first;
			int last_edge = q.front().second;
			q.pop();
			if (i == sink) {
				int flow = INT_MAX;
				for (int j = last_edge; j != -1; j = parent[j])
					flow = min(flow, edges[j].capacity - edges[j].flow);
				for (int j = last_edge; j != -1; j = parent[j])
					edges[j].flow += flow, edges[j ^ 1].flow -= flow;
				return flow;
			}
			for (const int& j : g[i])
				if (seen[edges[j].to] < current and edges[j].flow < edges[j].capacity)
					parent[j] = last_edge,
					seen[edges[j].to] = current,
					q.push({edges[j].to, j});
		}
		return 0;
	}
public:
	static int solve(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges) {
		vector<int> seen(N, 0);
		vector<int> parent(N, 0);
		int ans = 0, current = 0;
		while (int i = bfs(source, sink, g, edges, seen, parent, ++current))
			ans += i;
		return ans;
	}
};

class dinic {
//~ complexity: (vertexes * vertexes * edges)
private:
	dinic() {}
	static int bfs(const int& source, const int& sink, const vector< vector<int> >& g, const vector<edge>& edges, vector<int>& level) {
		for (int i = 0; i < N; ++i)
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
	static int dfs(const int& i, const int& sink, const int& flow, const vector< vector<int> >& g, vector<edge>& edges, const vector<int>& level, vector<int>& start) {
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
	static int solve(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges) {
		int ans = 0;
		vector<int> level(N, 0), start(N, 0);
		while (bfs(source, sink, g, edges, level)) {
			for (int i = 0; i < N; ++i)
				start[i] = 0;
			while (int i = dfs(source, sink, INT_MAX, g, edges, level, start))
				ans += i;
		}
		return ans;
	}
};

int main() {
	int n, m, games;
	vector<edge> edges;
	vector< vector<int> > g(N);
	int matches[N][N], points[N];
	while (scanf("%d %d %d", &n, &m, &games) == 3) {
		if (!n and !m and !games)
			break;
		edges.clear();
		for (int i = 0; i < N; ++i)
			g[i].clear();
		for (int i = 0; i < n; ++i) {
			points[i] = 0;
			for (int j = 0; j < n; ++j)
				if (i != j)
					matches[i][j] = m;
		}
		while (games-- > 0) {
			int x, y; char c; scanf("%d %c %d", &x, &c, &y);
			--matches[x][y];
			--matches[y][x];
			++points[y];
			if (c == '<')
				++points[y];
			else
				++points[x];
		}
		for (int i = 1; i < n; ++i)
			if (matches[0][i] > 0)
				points[0] += (matches[0][i] << 1),
				matches[0][i] = matches[i][0] = 0;
		int source = n;
		int sink = n + 1;
		bool valid = true;
		int total = points[0] - 1;
		for (int i = 1; i < n; ++i) {
			if (total - points[i] < 0)
				valid = false;
			else
				edge::add(i, sink, total - points[i], g, edges);
		}
		int need = 0;
		int current = sink;
		for (int i = 1; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if (matches[i][j] > 0)
					++current,
					matches[i][j] <<= 1,
					need += matches[i][j],
					edge::add(current, i, matches[i][j], g, edges),
					edge::add(current, j, matches[i][j], g, edges),
					edge::add(source, current, matches[i][j], g, edges);
		valid &= (dinic::solve(source, sink, g, edges) == need);
		printf("%s\n", valid ?  "Y" : "N");
	}
	return 0;
}