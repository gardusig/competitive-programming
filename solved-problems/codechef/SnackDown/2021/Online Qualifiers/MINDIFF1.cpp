#include <bits/stdc++.h>

void solve_test_case(const int test_case) {
  int N, M;
  std::cin >> N >> M;

  std::vector<std::set<int>> g(N);
  for (int i = 0; i < M; i += 1) {
    int x, y;
    std::cin >> x >> y;
    x -= 1;
    y -= 1;
    g[x].insert(y);
    g[y].insert(x);
  }

  std::multiset<std::pair<int, int>> remaining_vertexes;
  for (int i = 0; i < N; i += 1) {
    remaining_vertexes.insert({g[i].size(), i});
  }

  int current = N;
  int worst = 0;
  std::vector<int> ans(N, -1);
  while (!remaining_vertexes.empty()) {
    const int vertex = remaining_vertexes.begin()->second;
    remaining_vertexes.erase(remaining_vertexes.begin());

    if (ans[vertex] != -1) {
      continue;
    }

    worst = std::max(worst, int(g[vertex].size()));

    ans[vertex] = current;
    current -= 1;

    for (const int j : g[vertex]) {
      remaining_vertexes.erase({g[j].size(), j});
      g[j].erase(vertex);
      remaining_vertexes.insert({g[j].size(), j});
    }
  }

  std::cout << worst << '\n';
  for (int i = 0; i < N; i += 1) {
    std::cout << ans[i] << ' ';
  }
  std::cout << '\n';
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int tests;
  std::cin >> tests;
  for (int test_case = 1; test_case <= tests; test_case += 1) {
    solve_test_case(test_case);
  }
  return 0;
}