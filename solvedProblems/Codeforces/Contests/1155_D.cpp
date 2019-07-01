#include <bits/stdc++.h>
using namespace std;

const int N = 312345;

long long int solve(const auto &i, const auto &j, const auto &x, const auto &v, auto &dp) {
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  if (i == int(v.size())) {
    return dp[i][j] = 0;
  }
  long long int ans = 0;
  long long int value = 1LL * v[i] * (j == 1 ? x : 1);
  if (j > 0) {
    ans = max(ans, value + solve(i + 1, j - 1, x, v, dp));
  }
  ans = max(ans, value + solve(i + 1, j, x, v, dp));
  return dp[i][j] = ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, x;
  cin >> n >> x;
  vector< int > v(n);
  for (int i = 0; i < n; i += 1) {
    cin >> v[i];
  }
  long long int dp[N][3];
  memset(dp, -1, sizeof dp);
  long long int ans = 0;
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < 3; j += 1) {
      ans = max(ans, solve(i, j, x, v, dp));
    }
  }
  cout << ans << endl;
  return 0;
}