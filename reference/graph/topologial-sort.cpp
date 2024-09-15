#include <bits/stdc++.h>

namespace TopologicalSort {

std::vector<std::vector<int>> g;  // Adjacency list for the graph

// Kahn's Algorithm for Topological Sort (BFS-based)
std::vector<int> topologicalSortKahn(int N) {
  std::vector<int> degree(N, 0);  // In-degree of each node
  for (int i = 0; i < N; ++i) {
    for (const int &j : g[i]) {
      degree[j]++;
    }
  }
  std::queue<int> q;
  for (int i = 0; i < N; ++i) {
    if (degree[i] == 0) {
      q.push(i);  // Start with nodes having no incoming edges
    }
  }
  std::vector<int> result;
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    result.push_back(i);
    for (const int &j : g[i]) {
      if (--degree[j] == 0) {
        q.push(j);  // Add nodes with no remaining incoming edges
      }
    }
  }
  return result;
}

// Depth-First Search (DFS) based Topological Sort
void dfs(int i, std::vector<bool> &used, std::stack<int> &st) {
  used[i] = true;
  for (const int j : g[i]) {
    if (!used[j]) {
      dfs(j, used, st);
    }
  }
  st.push(i);  // Push node to stack after visiting all descendants
}

std::vector<int> topologicalSortDFS(int N) {
  std::stack<int> st;
  std::vector<bool> used(N, false);
  for (int i = 0; i < N; ++i) {
    if (!used[i]) {
      dfs(i, used, st);  // Run DFS for each unvisited node
    }
  }
  std::vector<int> result;
  while (!st.empty()) {
    result.push_back(st.top());
    st.pop();  // Extract nodes from stack in reverse finish order
  }
  return result;
}

}  // namespace TopologicalSort

// Test function for DFS-based Topological Sort
void testDFS() {
  TopologicalSort::g = {
      {1, 2},  // Node 0 -> Nodes 1 and 2
      {3},     // Node 1 -> Node 3
      {3},     // Node 2 -> Node 3
      {}       // Node 3 -> No outgoing edges
  };
  std::vector<int> result = TopologicalSort::topologicalSortDFS(4);
  std::vector<int> expected = {0, 1, 2, 3};
  std::unordered_set<int> resultSet(result.begin(), result.end());
  assert(resultSet.size() == 4);
  std::cout << "DFS Topological Sort Passed\n";
}

// Test function for Kahn's Algorithm
void testBFS() {
  TopologicalSort::g = {
      {1, 2},  // Node 0 -> Nodes 1 and 2
      {3},     // Node 1 -> Node 3
      {3},     // Node 2 -> Node 3
      {}       // Node 3 -> No outgoing edges
  };
  std::vector<int> result = TopologicalSort::topologicalSortKahn(4);
  std::vector<int> expected = {0, 1, 2, 3};
  std::unordered_set<int> resultSet(result.begin(), result.end());
  assert(resultSet.size() == 4);
  std::cout << "Kahn's Topological Sort Passed\n";
}

int main() {
  testDFS();
  testBFS();
  return 0;
}
