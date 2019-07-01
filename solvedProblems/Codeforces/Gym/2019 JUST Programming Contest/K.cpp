#include <bits/stdc++.h>
using namespace std;

vector< vector< int > > build_sparse_table(const auto &n, const auto &v) {
  int m = log2(n) + 1;
  vector< vector< int > > st(n, vector< int >(m));
  for (int i = 0; i < n; i += 1) {
    st[i][0] = v[i];
  }
  for (int j = 1; j < m; j += 1) {
    for (int i = 0; i + (1 << (j - 1)) < n; i += 1) {
      st[i][j] = st[i][j - 1] | st[i + (1 << (j - 1))][j - 1];
    }
  }
  return st;
}

int query(const auto &l, const auto &r, const auto &st) {
  int diff = r - l + 1;
  int pot = 31 - __builtin_clz(diff);
  int a = st[l][pot];
  int b = st[l + diff - (1 << pot)][pot];
  return a | b;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n;
    cin >> n;
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    unordered_set< int > ans;
    auto st = build_sparse_table(n, v);
    for (int i = 0; i < n; i += 1) {
      int lo = i;
      while (lo < n) {
        int hi = n - 1;
        int current = query(i, lo, st);
        ans.insert(current);
        while (lo <= hi) {
          const auto mid = lo + ((hi - lo) >> 1);
          if (current == query(i, mid, st)) {
            lo = mid + 1;
          } else {
            hi = mid - 1;
          }
        }
        lo = hi + 1;
      }
    }
    cout << ans.size() << endl;
  } 
  return 0;
}