#include <bits/stdc++.h>
using namespace std;

bool compare(const pair< int, double > &a, const pair< int, double > &b) {
  double kappa = a.first + b.first * a.second;
  double keepo = b.first + a.first * b.second;
  return kappa < keepo;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, w;
  cin >> n >> w;
  vector< pair< int, double > > v;
  for (int i = 0; i < n; i += 1) {
    int c; double r;
    cin >> c >> r;
    v.push_back({c, r});
  }
  sort(v.begin(), v.end(), compare);
  double ans = 0;
  double current = w;
  for (const auto &i: v) {
    ans += current * i.first;
    current *= i.second;
  }
  cout << fixed << setprecision(10) << ans << endl;
  return 0;
}