#include <bits/stdc++.h>

namespace FloydWarshall {

const int INF = 1e9 + 10;

std::vector<std::vector<int>> floydWarshall(
    int n, const std::vector<std::tuple<int, int, int>> &edges) {
  std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  for (const auto &[x, y, z] : edges) {
    dist[x][y] = std::min(dist[x][y], z);
    dist[y][x] = std::min(dist[y][x], z);
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] < INF && dist[k][j] < INF) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}
}  // namespace FloydWarshall

void testFloydWarshall() {
  int n = 4;
  std::vector<std::tuple<int, int, int>> edges = {
      {0, 1, 3}, {0, 2, 6}, {1, 2, 2}, {1, 3, 1}, {2, 3, 5}};
  auto dist = FloydWarshall::floydWarshall(n, edges);
  std::vector<std::vector<int>> expected = {
      {0, 3, 5, 4}, {3, 0, 2, 1}, {5, 2, 0, 3}, {4, 1, 3, 0}};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      assert(dist[i][j] == expected[i][j]);
    }
  }
  std::cout << "Floyd-Warshall Test Passed\n";
}

int main() {
  testFloydWarshall();
  return 0;
}
