#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector< int > v(n);
  unordered_map< int, vector< pair< int, int > > > g;
  for (int i = 0; i < n; i += 1) {
    cin >> v[i];
  }
  for (int i = 0; i < n; i += 1) {
    int current = 0;
    for (int j = i; j < n; j += 1) {
      current += v[j];
      g[current].push_back({i, j});
    }
  }
  for (const auto &i: g) {
    sort(g[i.first].begin(), g[i.first].end());
    cout << i.first << ':';
    for (const auto &j: i.second) {
      cout << " {" << j.first << ", " << j.second << "}";
    }
    cout << endl;
  }
  return 0;
}