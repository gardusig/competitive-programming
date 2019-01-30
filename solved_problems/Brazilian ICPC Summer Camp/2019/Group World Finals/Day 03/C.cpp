#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  map< string, multiset< int > > v;
  while (n-- > 0) {
    string s;
    int x;
    cin >> s >> x;
    v[s].insert(x);
  }
  int m; cin >> m;
  vector< string > input;
  bool ans = true;
  for (int i = 0; i < m; i += 1) {
    string s;
    cin >> s;
    input.push_back(s);
    if (v.count(s) == 0) {
      ans = false;
    }
  }
  int current = INT_MIN;
  for (const auto &i: input) {
    auto it = v[i].upper_bound(current);
    if (it == v[i].end()) {
      ans = false;
      break;
    }
    current = *it;
  }
  cout << (ans ? "Yes" : "No") << '\n';
  return 0;
}
