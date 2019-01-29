#include <bits/stdc++.h>
using namespace std;

int solve(const auto &s, const auto &v) {
  int lo = 1, hi = int(v.size());
  while (lo <= hi) {
    const auto mid = (lo + hi) / 2;
    vector< pair< int, int > > ls;
    for (int i = 0; i <= int(v.size()) - mid; i += 1) {
      int l = (i == 0) ? 0 : v[i - 1] + 1;
      int r = (i + mid < int(v.size())) ? v[i + mid] - 1 : int(s.size()) - 1;
      ls.push_back({0, v[i + mid - 1] - v[i] + 1});
      ls.push_back({1, r - l + 1});
    }
    sort(ls.begin(), ls.end());
    int current = 0;
    bool flag = false;
    for (const auto &i: ls) {
      if (i.first == 0) {
        current += 1;
      } else {
        current -= 1;
      }
      flag |= (current > 1);
    }
    if (flag == true) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return lo - 1;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  string s;
  cin >> s;
  int a = -1;
  int b = -1;
  int c = -1;
  int d = -1;
  if (s == string(int(s.size()), '0')) {
    a = 1;
    b = int(s.size()) - 1;
    c = 2;
    d = int(s.size());
  }
  else {
    vector< int > v;
    for (int i = 0; i < int(s.size()); i += 1) {
      if (s[i] == '1') {
        v.push_back(i);
      }
    }
    int kappaloiro = INT_MAX;
    const auto mid = solve(s, v);
    vector< pair< int, int > > ans;
    for (int i = 0; i <= int(v.size()) - mid; i += 1) {
      int l = (i == 0) ? 0 : v[i - 1] + 1;
      int r = (i + mid < int(v.size())) ? v[i + mid] - 1 : int(s.size()) - 1;
      ans.push_back({l, r});
      kappaloiro = min(kappaloiro, r - l + 1);
    }
    a = ans[0].first + 1;
    b = a + kappaloiro - 1;
    c = ans[1].first + 1;
    d = c + kappaloiro - 1;
  }
  cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
  return 0;
}