#include <bits/stdc++.h>
using namespace std;

namespace Tarjan {

const int N = 112345;
const int INF = 1e9;

class Edge {
 public:
  int to, id;
  Edge(int to, int id) : to(to), id(id) {}
};

vector<Edge> g[N];  // Graph adjacency list
int current_time, n, m;
int pre[N], low[N];  // pre[] stores discovery times, low[] stores the lowest
                     // discovery time reachable
bool used[N], bridge[N],
    articulation_point[N];  // Flags for visited nodes, bridges, and
                            // articulation points

// Tarjan's DFS to find bridges and articulation points
void dfsTarjan(int i, int p) {
  used[i] = true;
  pre[i] = low[i] = current_time++;  // Set discovery time
  int children = 0;                  // Number of child nodes in DFS tree
  for (const auto &e : g[i]) {
    int j = e.to;
    if (!used[j]) {
      ++children;
      dfsTarjan(j, i);               // DFS on child node
      low[i] = min(low[i], low[j]);  // Update low-link value
      if (low[j] > pre[i]) {
        bridge[e.id] = true;  // Bridge detected
      }
      if (i == p && children > 1) {
        articulation_point[i] = true;  // Root node is articulation point if it
                                       // has more than 1 child
      }
      if (i != p && low[j] >= pre[i]) {
        articulation_point[i] = true;  // Articulation point detected
      }
    } else if (j != p) {
      low[i] = min(low[i], pre[j]);  // Back edge, update low-link
    }
  }
}

// Build the graph and run Tarjan's algorithm
void buildTarjan(int _n, const vector<pair<int, int>> &edges) {
  n = _n;
  m = edges.size();
  current_time = 0;
  fill(used, used + n, false);  // Reset all arrays
  fill(articulation_point, articulation_point + n, false);
  fill(bridge, bridge + m, false);
  for (int i = 0; i < n; ++i) g[i].clear();  // Clear graph
  for (int i = 0; i < m; ++i) {              // Populate graph with edges
    int x = edges[i].first;
    int y = edges[i].second;
    g[x].emplace_back(y, i);
    g[y].emplace_back(x, i);
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) dfsTarjan(i, i);  // Run DFS for each component
  }
}

// Getters for bridges and articulation points
vector<bool> getBridges() { return vector<bool>(bridge, bridge + m); }
vector<bool> getArticulationPoints() {
  return vector<bool>(articulation_point, articulation_point + n);
}

}  // namespace Tarjan

// Test function for Tarjan's Algorithm
void testTarjan() {
  vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3},
                                  {3, 4}, {4, 5}, {5, 3}};
  Tarjan::buildTarjan(6, edges);

  vector<bool> bridges = Tarjan::getBridges();
  vector<bool> articulation_points = Tarjan::getArticulationPoints();

  // Test the correctness of the bridge detection
  for (int i = 0; i < 7; i += 1) {
    if (i == 3) {
      continue;
    }
    assert(bridges[i] == false);
  }
  assert(bridges[3] == true);

  // Test the correctness of articulation points
  assert(articulation_points[1] == true);
  assert(articulation_points[3] == true);
  assert(articulation_points[0] == false);
  assert(articulation_points[2] == false);
  assert(articulation_points[4] == false);

  cout << "Tarjan's Algorithm Test Passed\n";
}

int main() {
  testTarjan();
  return 0;
}
