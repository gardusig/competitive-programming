#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test += 1) {
    int n, p;
    cin >> n >> p;
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    sort(v.begin(), v.end());
    long long int current = 0;
    for (int i = 0; i < p - 1; i += 1) {
      current += (v[p - 1] - v[i]);
    }
    long long int ans = current;
    for (int i = p; i < n; i += 1) {
      current -= (v[i - p + 1] - v[i - p]);
      current += 1LL * (v[i] - v[i - 1]) * (p - 1);
      ans = min(ans, current);
    }
    cout << "Case #" << test << ": " << ans << endl;
  }
  return 0;
}