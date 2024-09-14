#include <bits/stdc++.h>
using namespace std;

namespace Kosaraju {

const int N = 112345;
const int MOD = 1000000007;

vector<int> g[N], t[N];  // g: original graph, t: transposed graph
bool used[N];
stack<int> aux;
vector<vector<int>> sccs;  // Stores all SCCs
int n, m;

void dfsG(int i) {
  used[i] = true;
  for (int j : g[i]) {
    if (!used[j]) dfsG(j);
  }
  aux.push(i);  // Push node onto stack after finishing DFS
}

void dfsT(int i, vector<int>& component) {
  used[i] = true;
  component.push_back(i);  // Collect nodes in current SCC
  for (int j : t[i]) {
    if (!used[j]) dfsT(j, component);
  }
}

void buildKosaraju(int _n, const vector<pair<int, int>>& edges) {
  n = _n;
  m = edges.size();
  // Reset graph and used array
  for (int i = 0; i < n; ++i) {
    g[i].clear();
    t[i].clear();
  }
  memset(used, false, sizeof used);
  // Build the original graph and transposed graph
  for (auto edge : edges) {
    int x = edge.first, y = edge.second;
    g[x].push_back(y);
    t[y].push_back(x);  // Transposed graph
  }
  // Step 1: Perform DFS on the original graph to compute finish times
  for (int i = 0; i < n; ++i) {
    if (!used[i]) dfsG(i);
  }
  // Step 2: Perform DFS on the transposed graph in reverse finish order
  memset(used, false, sizeof used);
  sccs.clear();  // Clear previous SCCs

  while (!aux.empty()) {
    int v = aux.top();
    aux.pop();
    if (!used[v]) {
      vector<int> component;
      dfsT(v, component);
      sccs.push_back(component);  // Store the SCC
    }
  }
}

vector<vector<int>> getSCCs() { return sccs; }

}  // namespace Kosaraju

void testKosaraju() {
  vector<pair<int, int>> edges = {
      {0, 1}, {1, 2}, {2, 0},  // First SCC
      {3, 4}, {4, 5}, {5, 3},  // Second SCC
      {1, 3}                   // Bridge between the two SCCs
  };
  Kosaraju::buildKosaraju(6, edges);
  vector<vector<int>> sccs = Kosaraju::getSCCs();
  assert(sccs.size() == 2);
  set<int> first_scc(sccs[0].begin(), sccs[0].end());
  set<int> second_scc(sccs[1].begin(), sccs[1].end());
  assert(first_scc == set<int>({0, 1, 2}));
  assert(second_scc == set<int>({3, 4, 5}));
  cout << "Kosaraju's Algorithm Test Passed\n";
}

int main() {
  testKosaraju();
  return 0;
}
