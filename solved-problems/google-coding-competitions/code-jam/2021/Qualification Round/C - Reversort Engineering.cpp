#include <bits/stdc++.h>

void solve_test_case(const int test) {
  int N, C;
  std::cin >> N >> C;
  std::cout << "Case #" << test << ":";
  if (C < N - 1) {
    std::cout << " IMPOSSIBLE" << std::endl;
    return;
  }
  C -= N - 1;
  std::vector<int> v;
  for (int i = 0; i < N; i += 1) {
    v.push_back(i);
  }
  int current = 1;
  std::vector<int> ans(N, -1);
  for (int i = 0; i < N - 1; i += 1) {
    const int current_cost = std::min(C, N - i - 1);
    C -= current_cost;
    const int pos = i + current_cost;
    ans[v[pos]] = current;
    current += 1;
    std::reverse(v.begin() + i, v.begin() + pos + 1);
  }
  if (C > 0) {
    std::cout << " IMPOSSIBLE" << std::endl;
    return;
  }
  ans[v.back()] = current;
  for (const int i : ans) {
    std::cout << " " << i;
  }
  std::cout << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}