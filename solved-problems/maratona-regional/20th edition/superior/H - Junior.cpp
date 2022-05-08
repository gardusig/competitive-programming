#include <bits/stdc++.h>

const int MOD = 1000000000 + 7;

class Edge {
 public:
  Edge(const int from, const int to, const int cost)
      : _from(from), _to(to), _cost(cost) {}

  int _from;
  int _to;
  int _cost;
};

std::pair<std::vector<int>, std::vector<int>> get_paths_with_shortest_distance(
    const int N, const int source, const int destination,
    const std::vector<std::vector<Edge>>& g) {
  std::vector<int> paths(N, 0);
  std::vector<int> dist(N, INT_MAX);
  std::priority_queue<std::pair<int, int>> pq;

  dist[source] = 0;
  paths[source] = 1;
  pq.emplace(-dist[source], source);

  while (!pq.empty()) {
    const int current_dist = -pq.top().first;
    const int vertex = pq.top().second;
    pq.pop();
    if (current_dist > dist[vertex]) {
      continue;
    }
    if (vertex == destination) {
      break;
    }
    for (const Edge& e : g[vertex]) {
      const int nxt_vertex = e._to;
      const int nxt_dist = current_dist + e._cost;
      if (nxt_dist > dist[nxt_vertex]) {
        continue;
      } else if (nxt_dist == dist[nxt_vertex]) {
        paths[nxt_vertex] += paths[vertex];
        paths[nxt_vertex] %= MOD;
      } else {
        paths[nxt_vertex] = paths[vertex];
        dist[nxt_vertex] = nxt_dist;
        pq.emplace(-dist[nxt_vertex], nxt_vertex);
      }
    }
  }

  return {paths, dist};
}

void solve(const int N, const std::vector<Edge>& edges, const int source,
           const int destination) {
  std::vector<std::vector<Edge>> g(N);
  for (const Edge& e : edges) {
    g[e._from].emplace_back(e._from, e._to, e._cost);
    g[e._to].emplace_back(e._to, e._from, e._cost);
  }

  const auto from_source =
      get_paths_with_shortest_distance(N, source, destination, g);
  const std::vector<int> paths_from_source = from_source.first;
  const std::vector<int> dist_from_source = from_source.second;

  const auto from_destination =
      get_paths_with_shortest_distance(N, destination, source, g);
  const std::vector<int> paths_from_destination = from_destination.first;
  const std::vector<int> dist_from_destination = from_destination.second;

  const int goal_dist = dist_from_source[destination];

  if (goal_dist == INT_MAX) {
    std::cout << "Grafo quebrado" << std::endl;
    return;
  }

  for (const Edge& e : edges) {
    const int x = e._from;
    const int y = e._to;
    const int cost = e._cost;

    int64_t current = 0;
    if (dist_from_source[x] + dist_from_destination[y] + cost == goal_dist) {
      current += (1LL * paths_from_source[x] * paths_from_destination[y]);
    }
    if (dist_from_source[y] + dist_from_destination[x] + cost == goal_dist) {
      current += (1LL * paths_from_source[y] * paths_from_destination[x]);
    }
    current %= MOD;

    std::cout << current << std::endl;
  }
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  std::vector<Edge> edges;
  for (int i = 0; i < M; i += 1) {
    int from, to, cost;
    std::cin >> from >> to >> cost;
    edges.emplace_back(from - 1, to - 1, cost);
  }

  int source, destination;
  std::cin >> source >> destination;

  solve(N, edges, source - 1, destination - 1);

  return 0;
}
