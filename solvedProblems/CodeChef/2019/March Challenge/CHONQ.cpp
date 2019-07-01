#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100000 + 5;

vector< vector< pair< int, int > > > build() {
  vector< vector< pair< int, int > > > v(MAX_SIZE);
  for (int i = 1; i < MAX_SIZE; i += 1) {
    int den = 1;
    while (true) {
      int value = i / den;
      if (value == 0) {
        v[i].push_back({value, INT_MAX});
        break;
      }
      int nxt_den = i / value;
      v[i].push_back({value, nxt_den - den + 1});
      den = nxt_den + 1;
    }
  }
  return v;
}

int solve(const auto &n, const auto &k, const auto &v, const auto &dp) {
  vector< long long int > sum(n + 5, 0);
  for (int i = n; i >= 0; i -= 1) {
    long long int j = i;
    for (const auto &k: dp[v[i]]) {
      sum[j + 1] -= k.first;
      j -= (k.second - 1);
      j = max(0LL, j);
      sum[j] += k.first;
      j -= 1;
      if (j < 0) {
        break;
      }
    }
  }
  int ans = 0;
  long long int current = 0;
  for (const auto &i: sum) {
    ans += 1;
    current += i;
    if (current <= k) {
      return ans;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  auto dp = build();
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, k;
    cin >> n >> k;
    vector< int > v(n + 5, 0);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    cout << solve(n, k, v, dp) << endl;
  }
  return 0;
}