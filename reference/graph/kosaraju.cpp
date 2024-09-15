#include <bits/stdc++.h>
using namespace std;

namespace Kosaraju {

// Define constants for the maximum number of nodes and a modulo value (though
// not used here).
const int N = 112345;
const int MOD = 1000000007;

// g: original graph, t: transposed graph
vector<int> g[N], t[N];

// used[]: keeps track of visited nodes in DFS.
// aux: stack to store nodes in the order of their finish times in the first
// DFS. sccs: stores all SCCs found in the graph.
bool used[N];
stack<int> aux;
vector<vector<int>> sccs;
int n, m;  // n: number of nodes, m: number of edges

// Performs DFS on the original graph `g`.
// This function is responsible for pushing nodes onto the stack `aux`
// in the order of their finish times.
void dfsG(int i) {
  used[i] = true;
  for (int j : g[i]) {
    if (!used[j]) dfsG(j);
  }
  aux.push(i);  // Push node onto the stack after exploring all neighbors
}

// Performs DFS on the transposed graph `t`.
// This function collects nodes of a strongly connected component (SCC) into
// `component`.
void dfsT(int i, vector<int>& component) {
  used[i] = true;
  component.push_back(i);  // Add the node to the current SCC
  for (int j : t[i]) {
    if (!used[j])
      dfsT(j, component);  // Visit all neighbors in the transposed graph
  }
}

// This function builds the SCCs of the graph using Kosaraju's Algorithm.
// Input:
//   - `_n`: number of nodes
//   - `edges`: a list of directed edges (pairs of integers) in the graph.
void buildKosaraju(int _n, const vector<pair<int, int>>& edges) {
  n = _n;
  m = edges.size();

  // Reset graph structures and the `used` array
  for (int i = 0; i < n; ++i) {
    g[i].clear();
    t[i].clear();
  }
  memset(used, false, sizeof used);

  // Build the original graph `g` and the transposed graph `t`
  for (auto edge : edges) {
    int x = edge.first, y = edge.second;
    g[x].push_back(y);  // Edge in the original graph
    t[y].push_back(x);  // Edge in the transposed graph (reverse direction)
  }

  // Step 1: Perform DFS on the original graph to compute the finishing times
  for (int i = 0; i < n; ++i) {
    if (!used[i]) dfsG(i);  // DFS for unvisited nodes
  }

  // Step 2: Perform DFS on the transposed graph in reverse finish order
  memset(used, false, sizeof used);  // Reset the `used` array
  sccs.clear();                      // Clear any previous SCCs

  // Process nodes in the order of decreasing finish time (from the stack)
  while (!aux.empty()) {
    int v = aux.top();
    aux.pop();
    if (!used[v]) {
      vector<int> component;
      dfsT(v, component);         // Find all nodes in the current SCC
      sccs.push_back(component);  // Store the SCC
    }
  }
}

// Returns the list of strongly connected components found by Kosaraju's
// algorithm.
vector<vector<int>> getSCCs() { return sccs; }

}  // namespace Kosaraju

// Function to test Kosaraju's Algorithm on a sample graph
void testKosaraju() {
  // A graph with 6 nodes and the following edges:
  //   - SCC1: (0 -> 1), (1 -> 2), (2 -> 0) (forming the first SCC)
  //   - SCC2: (3 -> 4), (4 -> 5), (5 -> 3) (forming the second SCC)
  //   - (1 -> 3) is a bridge between the two SCCs.
  vector<pair<int, int>> edges = {
      {0, 1}, {1, 2}, {2, 0},  // First SCC
      {3, 4}, {4, 5}, {5, 3},  // Second SCC
      {1, 3}                   // Bridge between the two SCCs
  };

  // Build the SCCs for a graph with 6 nodes and the above edges
  Kosaraju::buildKosaraju(6, edges);

  // Get the strongly connected components (SCCs)
  vector<vector<int>> sccs = Kosaraju::getSCCs();

  // We expect two SCCs:
  //   - First SCC: {0, 1, 2}
  //   - Second SCC: {3, 4, 5}
  assert(sccs.size() == 2);

  // Convert the components to sets for easier comparison
  set<int> first_scc(sccs[0].begin(), sccs[0].end());
  set<int> second_scc(sccs[1].begin(), sccs[1].end());

  // Verify that the first SCC is {0, 1, 2}
  assert(first_scc == set<int>({0, 1, 2}));

  // Verify that the second SCC is {3, 4, 5}
  assert(second_scc == set<int>({3, 4, 5}));

  // If all assertions pass, print a success message
  cout << "Kosaraju's Algorithm Test Passed\n";
}

int main() {
  // Run the test function to verify Kosaraju's algorithm
  testKosaraju();
  return 0;
}
