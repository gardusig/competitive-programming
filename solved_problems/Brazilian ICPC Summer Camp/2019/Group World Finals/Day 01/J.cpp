#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  while (true) {
    int n, q;
    cin >> n >> q;
    if (n == 0 and q == 0) {
      break;
    }
    vector< pair< pair< int, int >, string > > v;
    for (int i = 0; i < n; i += 1) {
      string s;
      int a, b;
      cin >> s >> a >> b;
      v.push_back({{b - a + 1, b}, s});
    }
    sort(v.begin(), v.end());
    while (q-- > 0) {
      int x;
      cin >> x;
      int lo = 0, hi = n - 1;
      bool found = false;
      while (lo <= hi) {
        const auto mid = (lo + hi) >> 1;
        if (x >= v[mid].first.first and x <= v[mid].first.second) {
          found = true;
          cout << v[mid].second << ' ' << x - v[mid].first.first + 1 << '\n';
          break;
        } else if (x < v[mid].first.first) {
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      }
      if (found == false) {
        cout << "Unknown" << '\n';
      }
    }
  }
  return 0;
}