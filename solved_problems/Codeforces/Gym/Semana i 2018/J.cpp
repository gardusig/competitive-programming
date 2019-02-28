#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

class node {
public:

  int lo;
  int hi;
  long double value;
  node *left;
  node *right;

  node(const auto &lo, const auto &hi) {
    this->lo = lo;
    this->hi = hi;
    this->value = 0.0;
    this->left = NULL;
    this->right = NULL;
    if (this->lo != this->hi) {
      const auto mid = this->lo + ((this->hi - this->lo) / 2);
      this->left = new node(this->lo, mid);
      this->right = new node(mid + 1, this->hi);
    }
  }

  void update(const auto &idx, const auto &value) {
    if (this->lo > idx or this->hi < idx) {
      return;
    }
    if (this->lo == idx and this->hi == idx) {
      this->value = value;
      return;
    }
    this->left->update(idx, value);
    this->right->update(idx, value);
    this->value = this->left->value * this->right->value;
  }

  long double query(const auto &l, const auto &r) {
    if (this->lo > r or this->hi < l) {
      return 1.0;
    }
    if (this->lo >= l and this->hi <= r) {
      return this->value;
    }
    const auto a = this->left->query(l, r);
    const auto b = this->right->query(l, r);
    return a * b;
  }
};

int main() {
  long double limit = 1.0;
  for (int i = 0; i < 100; i += 1) {
    limit *= 2.0;
  }
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  node *segtree = new node(0, n - 1);
  for (int i = 0; i < n; i += 1) {
    long double x;
    cin >> x;
    segtree->update(i, x);
  }
  int q;
  cin >> q;
  while (q-- > 0) {
    int type;
    cin >> type;
    if (type == 1) {
      int x, p;
      cin >> x >> p;
      segtree->update(x - 1, p);
    } else {
      int l, r;
      cin >> l >> r;
      long double ans = segtree->query(l - 1, r - 1);
      if (ans < limit) {
        cout << fixed << setprecision(10) << ans << endl;
      } else {
        cout << "INFINITE!" << endl;
      }
    }
  }
  return 0;
}