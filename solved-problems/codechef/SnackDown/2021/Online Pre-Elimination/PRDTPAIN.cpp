#include <bits/stdc++.h>

int64_t solve(const int N, const std::vector<int>& v) {
  int64_t ans = 0;
  for (int i = 0; i < N - 2; i += 1) {
    std::set<int> values;
    for (int j = i + 2; j < N; j += 1) {
      values.insert(v[j - 1]);
      const int goal = (v[j] + v[i]) >> 1;
      auto it = values.lower_bound(goal);
      if (it != values.begin()) {
        it--;
      }
      int64_t current = 0;
      for (int k = 0; k < 2; k += 1) {
        const int mid = *it;
        current = std::max(current, (int64_t)1LL * (mid - v[i]) * (v[j] - mid));
        if (it == values.end()) {
          break;
        }
        it++;
      }
      ans += current;
    }
  }
  return ans;
}

void solve_test_case() {
  int N;
  std::cin >> N;
  std::vector<int> v(N);
  for (auto& i : v) {
    std::cin >> i;
  }
  std::cout << solve(N, v) << std::endl;
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int tests;
  std::cin >> tests;
  for (int test_case = 1; test_case <= tests; test_case += 1) {
    solve_test_case();
  }
  return 0;
}
