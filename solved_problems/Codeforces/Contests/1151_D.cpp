#include <bits/stdc++.h>
using namespace std;

bool cmp(const pair< int, int > &x, const pair< int, int > &y) {
  int a = x.first * 1 + x.second * 1;
  int b = x.first * 2 + x.second * 0;
  int c = y.first * 2 + y.second * 0;
  int d = y.first * 1 + y.second * 1;
  return (a + c < b + d);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector< pair< int, int > > v(n);
  for (int i = 0; i < n; i += 1) {
    cin >> v[i].first >> v[i].second;
  }
  long long int ans = 0;
  sort(v.begin(), v.end(), cmp);
  for (int i = 0; i < n; i += 1) {
    ans += (1LL * v[i].first * i) + (1LL * v[i].second * (n - i - 1));
  }
  cout << ans << endl;
  return 0;
}