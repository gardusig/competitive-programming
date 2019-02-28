#include <bits/stdc++.h>
using namespace std;

class edge {
private:
  edge(const auto &to, const auto &flow, const auto &capacity) {
    this->to = to, this->flow = flow, this->capacity = capacity;
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
  static int bfs(const auto &source, const auto &sink, const auto &g, const auto &edges, auto &level, const auto &vertexes) {
    for (int i = 0; i < vertexes; ++i)
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
  static int solve(const auto &source, const auto &sink, const auto &g, auto &edges, const auto &vertexes) {
    int ans = 0;
    vector<int> level(vertexes), start(vertexes);
    while (bfs(source, sink, g, edges, level, vertexes) == true) {
      for (int i = 0; i < vertexes; ++i)
        start[i] = 0;
      for (int current_flow = INT_MAX; current_flow > 0; ans += current_flow)
        current_flow = dfs(source, sink, INT_MAX, g, edges, level, start);
    }
    return ans;
  }
};

void optmize_io() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}

bool valid(const auto &a, const auto &b, const auto &s) {
  long long kappa = 1LL * (a.first - b.first) * (a.first - b.first);
  long long keepo = 1LL * (a.second - b.second) * (a.second - b.second);
  return sqrt(kappa + keepo) < s;
}

int main() {
  optmize_io();
  int n, m, s; cin >> n >> m >> s;
  s -= 10;
  vector< pair< int, int > > beagles(n);
  for (int i = 0; i < n; ++i)
    cin >> beagles[i].first >> beagles[i].second;
  vector< pair< pair< int, int>, int > > bowls(m);
  for (int i = 0; i < m; ++i)
    cin >> bowls[i].first.first >> bowls[i].first.second >> bowls[i].second;
  int source = 0, sink = 1;
  int vertexes = n + m + 2;
  vector<edge> edges;
  vector< vector< int > > g(vertexes);
  for (int i = 0; i < n; ++i)
    edge::add(source, 2 + i, 1, g, edges);
  for (int j = 0; j < m; ++j)
    edge::add(2 + n + j, sink, bowls[j].second, g, edges);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (valid(beagles[i], bowls[j].first, s) == true)
        edge::add(2 + i, 2 + n + j, 1, g, edges);
  return cout << (dinic::solve(source, sink, g, edges, vertexes) == n ? "YES" : "NO") << '\n', 0;
}