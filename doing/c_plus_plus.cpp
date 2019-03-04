#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, k;
    cin >> n >> k;
    assert(n < 1123);
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    int ans = n;
    for (int i = 0; i < n; i += 1) {
      long long int current = 0;
      for (int j = i; j < n; j += 1) {
        current += v[j] / (j - i + 1);
      }
      if (current <= k) {
        cout << "valid: " << i << ", current: " << current << endl;
        ans = min(ans, i);
      }
    }
    cout << ans + 1 << endl;
  }
  return 0;
}