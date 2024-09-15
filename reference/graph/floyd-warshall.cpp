#include <bits/stdc++.h>

namespace FloydWarshall {

// Define a large constant for infinity, used to represent no direct path
// between nodes.
const int INF = 1e9 + 10;

// The Floyd-Warshall function computes all-pairs shortest paths.
// Input:
//  - `n`: The number of nodes in the graph.
//  - `edges`: A list of tuples representing edges in the format (u, v, w),
//  where
//             `u` and `v` are the nodes, and `w` is the weight of the edge
//             between them.
// Output:
//  - A 2D matrix `dist`, where `dist[i][j]` gives the shortest distance between
//  nodes `i` and `j`.
std::vector<std::vector<int>> floydWarshall(
    int n, const std::vector<std::tuple<int, int, int>> &edges) {
  // Initialize a distance matrix `dist` of size `n x n` with INF for all pairs.
  std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));

  // Set the diagonal of the distance matrix to 0, since the distance from any
  // node to itself is 0.
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }

  // Set the distances according to the input edges.
  // If multiple edges exist between two nodes, take the minimum weight.
  for (const auto &[x, y, z] : edges) {
    dist[x][y] =
        std::min(dist[x][y], z);  // Edge from `x` to `y` with weight `z`.
    dist[y][x] = std::min(
        dist[y][x], z);  // Edge from `y` to `x` (assuming an undirected graph).
  }

  // The core of the Floyd-Warshall algorithm.
  // For each node `k`, we check if the path from `i` to `j` via `k` is shorter
  // than the current path.
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        // If both `i` to `k` and `k` to `j` are reachable (not INF),
        // update the distance `i` to `j` with the shorter path.
        if (dist[i][k] < INF && dist[k][j] < INF) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  // Return the final distance matrix.
  return dist;
}
}  // namespace FloydWarshall

int main() {
  // Define a graph with 4 nodes and the following edges:
  //  - (0, 1) with weight 3
  //  - (0, 2) with weight 6
  //  - (1, 2) with weight 2
  //  - (1, 3) with weight 1
  //  - (2, 3) with weight 5
  int n = 4;
  std::vector<std::tuple<int, int, int>> edges = {
      {0, 1, 3}, {0, 2, 6}, {1, 2, 2}, {1, 3, 1}, {2, 3, 5}};
  // Call the Floyd-Warshall algorithm to compute the shortest distances.
  auto dist = FloydWarshall::floydWarshall(n, edges);
  // Define the expected output matrix, representing the shortest distances
  // between all pairs.
  std::vector<std::vector<int>> expected = {
      {0, 3, 5, 4},  // Distances from node 0 to nodes 0, 1, 2, 3
      {3, 0, 2, 1},  // Distances from node 1 to nodes 0, 1, 2, 3
      {5, 2, 0, 3},  // Distances from node 2 to nodes 0, 1, 2, 3
      {4, 1, 3, 0}   // Distances from node 3 to nodes 0, 1, 2, 3
  };
  // Verify the computed distance matrix matches the expected matrix.
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      assert(dist[i][j] == expected[i][j]);
    }
  }
  std::cout << "Floyd-Warshall Test Passed\n";
  return 0;
}
