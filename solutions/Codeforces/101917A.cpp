#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 1123456;
const int MOD = 1000000000 + 7;

void optmize_io() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}

int solve(const auto &n, auto &dp) {
  if (dp[n] != INT_MAX)
    return dp[n];
  if (n == 0)
    return dp[n] = 1;
  int ans = 0;
  for (int i = 1; i <= 8; ++i)
    if (i <= n)
      ans = (ans + solve(n - i, dp)) % MOD;
  return dp[n] = ans;
}

int main() {
  optmize_io();
  vector<int> dp(MAX_SIZE, INT_MAX);
  int T; cin >> T;
  while (T-- > 0) {
    int N; cin >> N;
    cout << solve(N / 3, dp) << '\n';
  }
  return 0;
}