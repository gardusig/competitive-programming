#include <bits/stdc++.h>
using namespace std;

namespace LCA {

// Constants
const int N = 1e5 + 10;  // Maximum number of nodes
const int M = 25;        // Log base 2 of maximum number of nodes

// Data structures for LCA computation
vector<pair<int, int>> g[N];  // Adjacency list for the graph (node, weight)
int lca[N][M];                // LCA table
int height[N];                // Height of each node in the tree
int highest[N][M];            // Highest weight on the path to ancestors

// Builds the LCA data structures
void buildLCA(int root, int wt, int parent) {
  lca[root][0] = parent;
  highest[root][0] = wt;
  height[root] = height[parent] + 1;

  // Build the LCA table for each power of 2
  for (int j = 1; j < M; ++j) {
    lca[root][j] = lca[lca[root][j - 1]][j - 1];
    highest[root][j] =
        max(highest[root][j - 1], highest[lca[root][j - 1]][j - 1]);
  }

  // Recursively build LCA for all children
  for (auto& edge : g[root]) {
    if (edge.first != parent) {
      buildLCA(edge.first, edge.second, root);
    }
  }
}

// Queries the LCA of nodes x and y
int queryLCA(int x, int y) {
  if (height[x] < height[y]) swap(x, y);

  // Bring x and y to the same level
  int diff = height[x] - height[y];
  for (int j = 0; j < M; ++j) {
    if (diff & (1 << j)) {
      x = lca[x][j];
    }
  }

  // If x and y are the same, return x as the LCA
  if (x == y) return x;

  // Move x and y up the tree until their parents are the same
  for (int j = M - 1; j >= 0; --j) {
    if (lca[x][j] != lca[y][j]) {
      x = lca[x][j];
      y = lca[y][j];
    }
  }

  return lca[x][0];
}

// Queries the highest weight on the path between nodes x and y
int queryHighest(int x, int y) {
  if (height[x] < height[y]) swap(x, y);

  int ans = 0;
  int diff = height[x] - height[y];

  // Find the highest weight on the path from x to the same level as y
  for (int j = 0; j < M; ++j) {
    if (diff & (1 << j)) {
      ans = max(ans, highest[x][j]);
      x = lca[x][j];
    }
  }

  // If x and y are the same, return the highest weight found
  if (x == y) return ans;

  // Find the highest weight on the path from x and y to their LCA
  for (int j = M - 1; j >= 0; --j) {
    if (lca[x][j] != lca[y][j]) {
      ans = max({ans, highest[x][j], highest[y][j]});
      x = lca[x][j];
      y = lca[y][j];
    }
  }

  return max({ans, highest[x][0], highest[y][0]});
}

// Initializes the graph for LCA calculations
void init(int numNodes, const vector<tuple<int, int, int>>& edges) {
  for (int i = 0; i < numNodes; ++i) {
    g[i].clear();
  }

  // Build the graph from the edges
  for (const auto& [x, y, z] : edges) {
    g[x].emplace_back(y, z);
    g[y].emplace_back(x, z);
  }

  height[0] = 0;      // Initialize the height of the root
  buildLCA(0, 0, 0);  // Build LCA structures starting from the root
}

}  // namespace LCA

void testLCA() {
  // Define a sample tree with weights
  int numNodes = 6;
  vector<tuple<int, int, int>> edges = {
      {0, 1, 2}, {0, 2, 4}, {1, 3, 6}, {1, 4, 8}, {2, 5, 10}};

  // Initialize the graph and build LCA structures
  LCA::init(numNodes, edges);

  // Perform queries and check results
  assert(LCA::queryLCA(3, 4) == 1);
  assert(LCA::queryHighest(3, 4) == 8);
  assert(LCA::queryLCA(5, 4) == 0);
  assert(LCA::queryHighest(5, 4) == 10);

  cout << "LCA Test Passed\n";
}

int main() {
  testLCA();
  return 0;
}
