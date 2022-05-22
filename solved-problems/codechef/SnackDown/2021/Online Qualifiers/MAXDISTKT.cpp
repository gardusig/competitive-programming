#include <bits/stdc++.h>

void solve_test_case(const int test_case) {
  int N;
  std::cin >> N;

  std::vector<std::pair<int, int>> v;
  for (int i = 0; i < N; i += 1) {
    int value;
    std::cin >> value;
    v.push_back({value, i});
  }

  std::sort(v.begin(), v.end());

  int current = 0;
  std::vector<int> ans(N);
  for (const auto& i : v) {
    const int value = i.first;
    const int idx = i.second;
    ans[idx] = current;
    if (current < value) {
      current += 1;
    }
  }

  for (const int i : ans) {
    std::cout << i << " ";
  }
  std::cout << "\n";
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
