#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  while (true) {
    int n, m;
    cin >> n >> m;
    if (n == 0 and m == 0) {
      break;
    }
    vector< pair< int, pair< int, int > > > v;
    for (int i = 0; i < m; i += 1) {
      int t, x, y; 
      cin >> t >> x >> y;
      x -= 1;
      y -= 1;
      v.push_back({t, {x, y}});
    }
    vector< bool > infected(n, false);
    infected[0] = true;
    sort(v.begin(), v.end());
    for (const auto &i: v) {
      int x = i.second.first;
      int y = i.second.second;
      if (infected[x] == true) {
        infected[y] = true;
      }
    }
    int ans = 0;
    for (int i = 0; i < n; i += 1) {
      ans += infected[i] == true;
    }
    cout << ans << '\n';
  }
  return 0;
}