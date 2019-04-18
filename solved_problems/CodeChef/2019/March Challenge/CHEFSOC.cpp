#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000000 + 7;

int solve(const auto &i, const auto &j, const auto &v, const auto &sum, auto &dp) {
  if (i >= int(v.size())) {
    return 0;
  }
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  int before = (j > 0) ? min(j, sum[i - 1]) : 0;
  int ans = 1 + before;
  if (j > 0) {
    if (v[i - 1] == 2) {
      ans = (ans + solve(i + 1, 0, v, sum, dp)) % MOD;
    }
    if (i + 1 < int(v.size()) and v[i + 1] == 2) {
      ans = (ans + before) % MOD;
    }
  }
  ans = (ans + solve(i + 1, 0, v, sum, dp)) % MOD;
  if (v[i] == 2) {
    ans = (ans + solve(i + 2, j + 1, v, sum, dp)) % MOD;
  }
  return dp[i][j] = ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n;
    cin >> n;
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    vector< int > sum(n, 0);
    for (int i = 0; i < n; i += 1) {
      sum[i] = 1;
      if (v[i] == 2 and i > 1) {
        sum[i] += sum[i - 2];
      }
    }
    vector< vector< int > > dp(n + 5, vector< int >(n + 5, -1));
    cout << solve(0, 0, v, sum, dp) << endl;
  }
  return 0;
}