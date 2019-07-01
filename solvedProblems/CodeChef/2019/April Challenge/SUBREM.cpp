#include <bits/stdc++.h>
using namespace std;

long long int solve(const auto &i, const auto &p, const auto &x, const auto &v, const auto &g) {
  long long int ans = v[i];
  for (const auto &j: g[i]) {
    if (j == p) {
      continue;
    }
    ans += max(solve(j, i, x, v, g), -1LL * x);
  }
  ans = max(ans, -1LL * x);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, x;
    cin >> n >> x;
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    vector< vector< int > > g(n);
    for (int i = 1; i < n; i += 1) {
      int x, y;
      cin >> x >> y;
      x -= 1;
      y -= 1;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    cout << solve(0, -1, x, v, g) << endl;
  }
  return 0;
}