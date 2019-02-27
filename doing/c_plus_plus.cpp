#include <bits/stdc++.h>
using namespace std;

class node {
public:

  int lo;
  int hi;
  int value;
  node *left;
  node *right;

  node(const auto &lo, const auto &hi) {
    this->lo = lo;
    this->hi = hi;
    this->value = 0;
    this->left = NULL;
    this->right = NULL;
    if (this->lo != this->hi) {
      const auto mid = this->lo + ((this->hi - this->lo) / 2);
      this->left = new node(this->lo, mid);
      this->right = new node(mid + 1, this->hi);
    }
  }

  void insert(const auto &idx) {
    if (this->lo > idx or this->hi < idx) {
      return;
    }
    if (this->lo == idx and this->hi == idx) {
      this->value += 1;
      return;
    }
    this->left->insert(idx);
    this->right->insert(idx);
    this->value = this->left->value + this->right->value;
  }

  int ask(const auto &need) {
    cout << this->lo << ' ' << this->hi << ' ' << this->value << endl;
    if (this->value < need) {
      return -1;
    }
    if (this->lo == this->hi) {
      return this->lo;
    }
    if (this->left->value < need) {
      return this->right->ask(need - this->left->value);
    }
    return this->left->ask(need);
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, k;
  cin >> n >> k;
  set< int > s;
  map< int, int > Hash, Unhash;
  vector< vector< int > > v(n, vector< int >(3));
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < 3; j += 1) {
      cin >> v[i][j];
      s.insert(v[i][j]);
    }
  }
  int size = 0;
  for (const auto &i: s) {
    Hash[i] = size;
    Unhash[size] = i;
    size += 1;
  }
  sort(v.begin(), v.end());
  vector< vector< pair< int, int > > > g(n);
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j <= i; j += 1) {
      g[i].push_back({v[j][1], v[j][2]});
    }
    sort(g[i].begin(), g[i].end());
  }
  long long int ans = LLONG_MAX;
  for (int i = 0; i < n; i += 1) {
    node *segtree = new node(0, n);
    for (int j = 0; j <= i; j += 1) {
      cout << i << " insert: " << g[i][j].second << " -> " << Hash[g[i][j].second] << endl;
      segtree->insert(Hash[g[i][j].second]);
      if (j + 1 >= k) {
        ans = min(ans, 0LL + v[i][0] + g[i][j].first + Unhash[segtree->ask(k)]);
        cout << i << ' ' << j << ": " << v[i][0] << ' ' << g[i][j].first << ' ' << Unhash[segtree->ask(k)] << endl;
      }
    }
  }
  cout << ans << endl;
  return 0;
}