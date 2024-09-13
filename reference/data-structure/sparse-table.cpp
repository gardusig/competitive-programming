#include <bits/stdc++.h>

namespace sparse {

template <typename T, typename Merge>
class SparseTable {
 private:
  std::vector<std::vector<T>> st;
  int n, m;
  Merge merge;

 public:
  SparseTable(const std::vector<T>& v, Merge mergeFunc) : merge(mergeFunc) {
    n = int(v.size());
    m = log2(n) + 1;
    st.assign(n, std::vector<T>(m));
    for (int i = 0; i < n; i++) {
      st[i][0] = v[i];
    }
    for (int j = 1; j < m; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  T query(int l, int r) const {
    int diff = r - l + 1;
    int pot = 31 - __builtin_clz(diff);
    return merge(st[l][pot], st[r - (1 << pot) + 1][pot]);
  }
};
auto mergeOr = [](int a, int b) { return a | b; };
auto mergeSum = [](int a, int b) { return a + b; };
auto mergeGcd = [](int a, int b) { return std::gcd(a, b); };
}  // namespace sparse

int main() {
  std::vector<int> v = {1, 2, 4, 8, 16, 32, 64, 128};
  sparse::SparseTable<int, decltype(sparse::mergeOr)> sparseTable(
      v, sparse::mergeOr);
  assert(sparseTable.query(0, 0) == 1);
  assert(sparseTable.query(0, 2) == 7);
  assert(sparseTable.query(2, 2) == 4);
  assert(sparseTable.query(0, 7) == 255);
  assert(sparseTable.query(1, 3) == 14);
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
