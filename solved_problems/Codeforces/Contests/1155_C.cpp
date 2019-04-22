#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  vector< long long int > x(n);
  for (int i = 0; i < n; i += 1) {
    cin >> x[i];
  }
  long long int need = 0;
  for (int i = 1; i < n; i += 1) {
    need = __gcd(need, x[i] - x[i - 1]);
  }
  for (int i = 1; i <= m; i += 1) {
    long long int kappa;
    cin >> kappa;
    if ((need % kappa) == 0) {
      cout << "YES" << endl;
      cout << x[0] << ' ' << i << endl;
      return 0;
    }
  }
  cout << "NO" << endl;
  return 0;
}