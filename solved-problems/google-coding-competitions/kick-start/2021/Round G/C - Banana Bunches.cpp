#include <bits/stdc++.h>

int solve(const int N, const int K, const std::vector<int>& v) {
  int ans = INT_MAX;

  std::vector<int> dp(K + 1, INT_MAX);
  dp[0] = 0;

  for (int i = 0; i < N; i += 1) {
    int current = 0;
    for (int j = i; j < N; j += 1) {
      current += v[j];
      const int size = j - i + 1;
      if (current > K) {
        break;
      }
      const int need = K - current;
      if (dp[need] != INT_MAX) {
        ans = std::min(ans, size + dp[need]);
      }
    }

    current = 0;
    for (int j = i; j >= 0; j -= 1) {
      current += v[j];
      const int size = i - j + 1;
      if (current > K) {
        break;
      }
      dp[current] = std::min(dp[current], size);
    }
  }

  if (ans == INT_MAX) {
    ans = -1;
  }

  return ans;
}

void solve_test_case(const int test_case) {
  int N, K;
  std::cin >> N >> K;
  std::vector<int> V(N);
  for (int& i : V) {
    std::cin >> i;
  }

  const int ans = solve(N, K, V);
  std::cout << "Case #" << test_case << ": " << ans << '\n';
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