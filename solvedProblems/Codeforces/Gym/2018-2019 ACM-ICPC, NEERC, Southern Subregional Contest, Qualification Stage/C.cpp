#include <bits/stdc++.h>
using namespace std;
 
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  if (n == 1) {
    cout << 0 << endl;
    return 0;
  }
  vector< int > v(n);
  for (int i = 0; i < n; i += 1) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  for (int i = 1; i < n; i += 1) {
    if ((v[i] % v[0]) != 0 or __builtin_popcount(v[i] / v[0]) != 1) {
      cout << -1 << endl;
      return 0;
    }
  }
  map< int, int > qtd;
  map< int, int > have;
  const int kappaloiro = v[0];
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; true; j += 1) {
      if ((1LL << j) == (v[i] / kappaloiro)) {
        v[i] = j;
        qtd[j] += 1;
        have[j] += 1;
        break;
      }
    }
  }
  int ans = 0;
  int total = 0;
  for (int i = 0; true; i += 1) {
    if (have[i] == 1 and total == n) {
      break;
    }
    total += qtd[i];
    ans += (have[i] & 1);
    have[i + 1] += (have[i] + 1) >> 1;
  }
  cout << ans << endl;
  return 0;
}