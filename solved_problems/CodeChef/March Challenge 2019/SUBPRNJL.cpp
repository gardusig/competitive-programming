#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 2123;

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

  int ask(const auto &k, const auto &qtd) {
    if (this->lo == this->hi) {
      return this->lo;
    }
    if (this->left->value * qtd >= k) {
      return this->left->ask(k, qtd);
    }
    return this->right->ask(k - (this->left->value * qtd), qtd);
  }

  int query(const auto &idx) {
    if (this->lo > idx or this->hi < idx) {
      return 0;
    }
    if (this->lo == idx and this->hi == idx) {
      return this->value;
    }
    const auto a = this->left->query(idx);
    const auto b = this->right->query(idx);
    return a + b;
  }

  void clear() {
    this->value = 0;
    if (this->lo != this->hi) {
      this->left->clear();
      this->right->clear();
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, k;
    cin >> n >> k;
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    int ans = 0;
    node *segtree = new node(0, MAX_SIZE);
    for (int i = 0; i < n; i += 1) {
      segtree->clear();
      for (int j = i; j < n; j += 1) {
        segtree->insert(v[j]);
        int size = j - i + 1;
        int x = segtree->ask(k, (k + size - 1) / size);
        int f = segtree->query(x);
        if (segtree->query(f) > 0) {
          ans += 1;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}