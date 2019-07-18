#include <bits/stdc++.h>
using namespace std;

vector< vector< int > > build(const auto &n, const auto &s) {
  vector< vector< int > > l(n, vector< int >(n, 0));
  for (int i = 0; i < n; i += 1) {
    string kappa = "";
    for (int j = i; j < n; j += 1) {
      kappa.push_back(s[j]);
      string keepo = kappa;
      reverse(keepo.begin(), keepo.end());
      if (j > i) {
        l[i][j] = l[i][j - 1];
      }
      l[i][j] += (kappa == keepo);
    }
  }
  vector< vector< int > > r(n, vector< int >(n, 0));
  for (int i = n - 1; i >= 0; i -= 1) {
    string kappa = "";
    for (int j = i; j >= 0; j -= 1) {
      kappa.push_back(s[j]);
      string keepo = kappa;
      reverse(keepo.begin(), keepo.end());
      if (j < i) {
        r[j][i] = r[j + 1][i];
      }
      r[j][i] += (kappa == keepo);
    }
  }
  vector< vector< int > > sum(n, vector< int >(n, 0));
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < n; j += 1) {
      sum[i][j] = l[i][j] + r[i][j];
    }
  }
  return sum;
}

long long int solve(const auto &i, const auto &j, const auto &s, const auto &palindrome, auto &dp) {
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  long long int ans = 0;
  if (s[i] == s[j]) {
    ans += 1;
    if (i + 1 < j) {
      ans += palindrome[i + 1][j - 1];
    }
    if (i + 1 < j - 1) {
      ans += solve(i + 1, j - 1, s, palindrome, dp);
    }
  }
  return dp[i][j] = ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  string s;
  cin >> s;
  int n = int(s.size());
  long long int ans = 0;
  auto palindrome = build(n, s);
  vector< vector< long long int > > dp(n, vector< long long int >(n, -1));
  for (int i = 0; i < n; i += 1) {
    for (int j = i + 1; j < n; j += 1) {
      ans += solve(i, j, s, palindrome, dp);
    }
  }
  cout << ans << endl;
  return 0;
}