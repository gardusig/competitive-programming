#include <bits/stdc++.h>
using namespace std;

class food {
public:
  int eat;
  int energy;
  int lose;

  bool operator < (const auto &other) {
    auto a = 1LL * this->eat * other.lose;
    auto b = 1LL * other.eat * this->lose;
    return a < b;
  }
};

int solve(const auto &i, const auto &j, const auto &v, auto &dp) {
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  if (i == int(v.size())) {
    return dp[i][j] = 0;
  }
  int ans = 0;
  ans = max(ans, solve(i + 1, j, v, dp));
  ans = max(ans, max(0, v[i].energy - (j * v[i].lose)) + solve(i + 1, j + v[i].eat, v, dp));
  return dp[i][j] = ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test += 1) {
    int n;
    cin >> n;
    vector< food > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i].eat >> v[i].energy >> v[i].lose;
    }
    int dp[112][11234];
    memset(dp, -1, sizeof dp);
    sort(v.begin(), v.end());
    cout << "Case #" << test << ": " << solve(0, 0, v, dp) << endl;
  }
  return 0;
}