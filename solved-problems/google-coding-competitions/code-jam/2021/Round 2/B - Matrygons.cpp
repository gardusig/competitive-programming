#include <bits/stdc++.h>

const int MAX_SIZE = 1'000 + 1;

std::unordered_map<int, int> dp[MAX_SIZE];

int solve(const int sum, const int last) {
  if (dp[sum].count(last)) {
    return dp[sum][last];
  }
  if (sum == 0) {
    dp[sum][last] = 0;
    return dp[sum][last];
  }
  dp[sum][last] = -1e8;
  for (int i = 1; 1LL * i * i <= last; i += 1) {
    if (last % i) {
      continue;
    }
    for (const int j : {i, last / i}) {
      if (j < 3 or j == last or j > sum) {
        continue;
      }
      dp[sum][last] = std::max(dp[sum][last], 1 + solve(sum - j, j));
    }
  }
  return dp[sum][last];
}

void solve_test_case(const int test) {
  int N;
  std::cin >> N;
  int ans = 0;
  for (int i = 1; i <= N; i += 1) {
    ans = std::max(ans, 1 + solve(N - i, i));
  }
  std::cout << "Case #" << test << ": " << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}