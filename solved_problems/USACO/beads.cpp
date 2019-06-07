#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("beads.in", "r", stdin);
  freopen("beads.out", "w", stdout);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  string s;
  cin >> n >> s;
  n += n;
  s += s;
  unordered_map< char, int > last;
  last['r'] = -1;
  last['b'] = -1;
  vector< int > l(n);
  for (int i = 0; i < n; i += 1) {
    const char &c = s[i];
    if (c == 'r') {
      l[i] = i - last['b'];
    } else if (c == 'b') {
      l[i] = i - last['r'];
    } else {
      l[i] = i - min(last['r'], last['b']);
    }
    last[c] = i;
  }
  last['r'] = n;
  last['b'] = n;
  vector< int > r(n);
  for (int i = n - 1; i >= 0; i -= 1) {
    const char &c = s[i];
    if (c == 'r') {
      r[i] = last['b'] - i;
    } else if (c == 'b') {
      r[i] = last['r'] - i;
    } else {
      r[i] = max(last['r'], last['b']) - i;
    }
    last[c] = i;
  }
  int ans = r[0];
  for (int i = 1; i < n; i += 1) {
    ans = max(ans, l[i - 1] + r[i]);
  }
  cout << min(n / 2, ans) << endl;
  return 0;
}