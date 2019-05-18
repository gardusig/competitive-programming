#include <bits/stdc++.h>
using namespace std;

class node {
public:
  
  int lo;
  int hi;
  int sum;
  int lazy;
  int value;
  node *left;
  node *right;
  
  node(const auto &lo, const auto &hi, auto &values) {
    this->lo = lo;
    this->hi = hi;
    this->sum = 0;
    this->lazy = 0;
    if (lo == hi) {
      this->left = NULL;
      this->right = NULL;
      this->value = values[lo] - values[lo - 1];
    } else {
      const auto mid = this->lo + ((this->hi - this->lo) >> 1);
      this->left = new node(lo, mid, values);
      this->right = new node(mid + 1, hi, values);
      this->value = this->left->value + this->right->value;
    }
  }
  
  void propagate() {
    if (this->lazy != 0) {
      if (this->lo != this->hi) {
        this->left->lazy ^= 1;
        this->right->lazy ^= 1;
      }
      this->lazy = 0;
      this->sum = this->value - this->sum;
    }    
  }
  
  void flip(const auto &l, const auto &r) {
    this->propagate();
    if (this->hi < l or this->lo > r) {
      return;
    }
    if (this->lo >= l and this->hi <= r) {
      this->lazy ^= 1;
      this->propagate();
      return;
    }
    this->left->flip(l, r);
    this->right->flip(l, r);
    this->sum = this->left->sum + this->right->sum;
  }
  
  int query(const auto &l, const auto &r) {
    this->propagate();
    if (this->hi < l or this->lo > r) {
      return 0;
    }
    if (this->lo >= l and this->hi <= r) {
      return this->sum;
    }
    const auto &a = this->left->query(l, r);
    const auto &b = this->right->query(l, r);
    return a + b;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  set< int > s;
  vector< pair< pair< int, int >, pair< int, int > > > v;
  for (int i = 0; i < n; i += 1) {
    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    if (ax > bx) {
      swap(ax, bx);
    }
    if (ay > by) {
      swap(ay, by);
    }
    s.insert(ay);
    s.insert(by);
    v.push_back({{ax, 0}, {ay, by}});
    v.push_back({{bx, 1}, {ay, by}});
  }
  unordered_map< int, int > convert;
  unordered_map< int, int > recover;
  for (const auto &i: s) {
    convert[i] = int(recover.size());
    recover[convert[i]] = i;
  }
  int last = -1;
  long long int ans = 0;
  sort(v.begin(), v.end());
  node *segtree = new node(1, int(recover.size()) - 1, recover);
  for (const auto &i: v) {
    if (last != -1) {
      ans += 1LL * (i.first.first - last) * segtree->query(1, int(convert.size()) - 1);
    }
    int x = i.second.first;
    int y = i.second.second;
    segtree->flip(convert[x] + 1, convert[y]);
    last = i.first.first;
  }
  cout << ans << endl;
  return 0;
}
