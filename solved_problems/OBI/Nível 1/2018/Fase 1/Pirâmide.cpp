#include <bits/stdc++.h>
using namespace std;

int solve(const auto &i, const auto &j, const auto &k, const auto &sum, auto &dp) {
  if (dp[i][j][k] != -1) {
    return dp[i][j][k];
  }
  int current = sum[i][k + 1] - sum[i][j];
  if (j == k) {
    return dp[i][j][k] = current;
  }
  int nxt = min(solve(i - 1, j + 1, k, sum, dp), solve(i - 1, j, k - 1, sum, dp));
  return dp[i][j][k] = current + nxt;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector< vector< vector< int > > > dp(n + 5);
  vector< vector< int > > sum(n + 5, vector< int >(n + 5));
  for (int i = 0; i < n; i += 1) {
    dp[i].resize(n + 5);
    sum[i][0] = 0;
    for (int j = 0; j < n; j += 1) {
      dp[i][j] = vector< int > (n, -1);
      int value;
      cin >> value;
      sum[i][j + 1] = sum[i][j] + value;
    }
  }
  cout << solve(n - 1, 0, n - 1, sum, dp) << endl;
  return 0;
}