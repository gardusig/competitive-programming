#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, m;
    cin >> n >> m;
    vector< int > a, b;
    for (int i = 0; i < n; i += 1) {
      int x;
      cin >> x;
      a.push_back(x);
    }
    for (int i = 0; i < m; i += 1) {
      int x;
      cin >> x;
      b.push_back(x);
    }
    long long ans = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < n; i += 1) {
      int lo = 0, hi = m - 1;
      while (lo <= hi) {
        const auto mid = (lo + hi) >> 1;
        if (a[i] > b[mid]) {
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
      ans += lo;
    }
    cout << ans << '\n';
  }
  return 0;
}