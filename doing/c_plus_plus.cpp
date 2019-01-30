#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  freopen("electricity.in", "r", stdin);
  freopen("electricity.out", "w", stdout);
  int n, m;
  cin >> n >> m;
  vector< int > a(n), b(m);
  for (int i = 0; i < n; i += 1) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i += 1) {
    cin >> b[i];
  }
  sort(a.rbegin(), a.rend());
  sort(b.rbegin(), b.rend());
  int ans = 1;
  int a_have = 1;
  int b_have = 0;
  int i = 0, j = 0;
  while (true) {
    if ((a_have > 0 and i < m) == false) {
      break;
    }
    while (a_have > 0 and i < m) {
      a_have -= 1;
      b_have += a[i];
      i += 1;
    }
    if ((b_have > 0 and j < m) == false) {
      break;
    }
    while (b_have > 0 and j < m) {
      b_have -= 1;
      a_have += b[j];
      j += 1;
    }
    ans = max(ans, a_have);
  }
  cout << ans << '\n';
  return 0;
}