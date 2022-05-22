#include <bits/stdc++.h>

std::vector<int64_t> fib;
std::map<int64_t, bool> dp;

void build_fib(const int64_t LIMIT) {
  fib.push_back(1);
  fib.push_back(2);
  while (fib.back() < LIMIT) {
    fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
  }
}

bool is_divisible_by_fib_factors(const int64_t N) {
  if (dp.count(N)) {
    return dp[N];
  }
  if (N == 1) {
    return dp[N] = true;
  }
  dp[N] = false;
  for (int i = fib.size() - 1; i > 0; i -= 1) {
    if ((N % fib[i]) == 0) {
      dp[N] |= is_divisible_by_fib_factors(N / fib[i]);
    }
  }
  return dp[N];
}

std::string solve(const int64_t N) {
  if (N == 1) {
    return "";
  }
  for (int i = fib.size() - 1; i > 0; i -= 1) {
    if ((N % fib[i]) == 0 and is_divisible_by_fib_factors(N / fib[i])) {
      return std::string(i, 'A') + "B" + solve(N / fib[i]);
    }
  }
  return "IMPOSSIBLE";
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int64_t N;
  std::cin >> N;
  build_fib(N);
  std::cout << solve(N) << std::endl;
  return 0;
}