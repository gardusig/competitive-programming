#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test += 1) {
    int n;
    cin >> n;
    vector< string > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
      reverse(v[i].begin(), v[i].end());
    }
    priority_queue< pair< int, pair< int, int > > > pq;
    for (int i = 0; i < n; i += 1) {
      for (int j = i + 1; j < n; j += 1) {
        for (int k = 0; k < min(v[i].size(), v[j].size()); k += 1) {
          if (v[i][k] != v[j][k]) {
            break;
          }
          pq.push({k, {i, j}});
        }
      }
    }
    int ans = 0;
    vector< bool > used(n, false);
    unordered_set< string > suffix;
    while (pq.empty() == false) {
      const auto size = pq.top().first;
      const auto i = pq.top().second.first;
      const auto j = pq.top().second.second;
      pq.pop();
      string current = v[i].substr(0, size + 1);
      if (used[i] == true or used[j] == true or suffix.count(current)) {
        continue;
      }
      ans += 2;
      used[i] = true;
      used[j] = true;
      suffix.insert(current);
    }
    cout << "Case #" << test << ": " << ans << endl;
  }
  return 0;
}