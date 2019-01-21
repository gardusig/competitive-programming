#include <bits/stdc++.h>
using namespace std;

double solve_valid(const auto &n, const auto &m, auto &dp) {
  if (dp[n][m] != INT_MIN) {
    return dp[n][m];
  }
  if (n == 0) {
    return dp[n][m] = (m > 0);
  }
  double ans = solve_valid(n - 1, m, dp) * 2;
  if (m > 0) {
    ans += solve_valid(n - 1, m - 1, dp);
  }
  return dp[n][m] = ans;
}

double solve_total(const auto &n, const auto &m, auto &dp) {
  if (dp[n][m] != INT_MIN) {
    return dp[n][m];
  }
  if (n == 0) {
    return dp[n][m] = 1;
  }
  double ans = solve_total(n - 1, m, dp) * 2;
  if (m > 0) {
    ans += solve_total(n - 1, m - 1, dp);
  }
  return dp[n][m] = ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  while (cin >> n >> m) {
    vector< vector< double > > dp;
    dp = vector< vector< double > >(n + 5, vector< double >(m + 5, INT_MIN));
    double valid = solve_valid(n, m, dp);
    dp = vector< vector< double > >(n + 5, vector< double >(m + 5, INT_MIN));
    double total = solve_total(n, m, dp);
    if (valid < 1e-6 or total < 1e-6) {
      cout << setprecision(10) << fixed << 0 << '\n';
    } else {
      cout << setprecision(10) << fixed << 100.0 * valid / total << '\n';
    }
  }
  return 0;
}