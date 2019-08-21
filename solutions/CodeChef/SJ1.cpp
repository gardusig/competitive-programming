#include <bits/stdc++.h>
using namespace std;

void solve(const auto &i, const auto &p, const auto &value, const auto &v, const auto &mod, const auto &g, auto &ans) {
  bool leaf = true;
  long long int nxt_value = __gcd(v[i], value);
  for (const auto &j: g[i]) {
    if (j == p) {
      continue;
    }
    leaf = false;
    solve(j, i, nxt_value, v, mod, g, ans);
  }
  if (leaf == true) {
    long long int gcd = __gcd(nxt_value, mod[i]);
    ans.push_back({i, mod[i] - gcd});
  }
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
    vector< vector< int > > g(n);
    for (int i = 1; i < n; i += 1) {
      int x, y;
      cin >> x >> y;
      x -= 1;
      y -= 1;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    vector< long long int > v(n);
    vector< long long int > mod(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    for (int i = 0; i < n; i += 1) {
      cin >> mod[i];
    }
    vector< pair< int, long long int > > ans;
    solve(0, -1, v[0], v, mod, g, ans);
    sort(ans.begin(), ans.end());
    for (const auto &i: ans) {
      cout << i.second << ' ';
    }
    cout << endl;
  }
  return 0;
}