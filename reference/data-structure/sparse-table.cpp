#include <bits/stdc++.h>

namespace sparse {

// Template-based SparseTable class for range queries.
// The class works for any type `T` and a custom merge function `Merge`.
template <typename T, typename Merge>
class SparseTable {
 private:
  std::vector<std::vector<T>>
      st;  // The sparse table storing precomputed results.
  int n,
      m;  // `n` is the size of the input, `m` is the maximum power of 2 needed.
  Merge merge;  // Function to merge two elements (e.g., sum, gcd, etc.).

 public:
  // Constructor to initialize the SparseTable with a given vector `v` and merge
  // function.
  SparseTable(const std::vector<T>& v, Merge mergeFunc) : merge(mergeFunc) {
    n = int(v.size());  // Get the size of the input vector.
    m = log2(n) + 1;    // Maximum number of columns required (log2(n) levels).

    // Initialize the sparse table with dimensions [n][m].
    st.assign(n, std::vector<T>(m));

    // Base case: Fill the first column of the sparse table with the original
    // values.
    for (int i = 0; i < n; i++) {
      st[i][0] = v[i];  // The 0-th column holds the original array values.
    }

    // Build the sparse table. The idea is to precompute answers for ranges
    // of length 2^j using results of smaller ranges.
    for (int j = 1; j < m; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        // Merge results from two halves: st[i][j-1] and st[i + (1 << (j -
        // 1))][j - 1].
        st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  // Query function to get the result for the range [l, r].
  // It breaks the range into two overlapping intervals of length 2^k.
  T query(int l, int r) const {
    int diff = r - l + 1;  // Length of the query range.
    int pot =
        31 - __builtin_clz(diff);  // Compute the largest power of 2 <= diff.

    // Merge the two segments that cover the range [l, r].
    return merge(st[l][pot], st[r - (1 << pot) + 1][pot]);
  }
};

// Examples of different merge functions:
// Merge function for bitwise OR operation.
auto mergeOr = [](int a, int b) { return a | b; };

// Merge function for sum operation.
auto mergeSum = [](int a, int b) { return a + b; };

// Merge function for GCD operation.
auto mergeGcd = [](int a, int b) { return std::gcd(a, b); };

}  // namespace sparse

int main() {
  // Example usage: constructing a SparseTable with the bitwise OR operation.
  std::vector<int> v = {1, 2, 4, 8, 16, 32, 64, 128};
  // Construct the sparse table using the bitwise OR merge function.
  sparse::SparseTable<int, decltype(sparse::mergeOr)> sparseTable(
      v, sparse::mergeOr);
  // Test cases to validate the correctness of the SparseTable.
  assert(sparseTable.query(0, 0) == 1);  // Query range [0, 0], expect 1.
  assert(sparseTable.query(0, 2) ==
         7);  // Query range [0, 2], expect 1 | 2 | 4 = 7.
  assert(sparseTable.query(2, 2) == 4);  // Query range [2, 2], expect 4.
  assert(sparseTable.query(0, 7) ==
         255);  // Query range [0, 7], expect 1 | 2 | ... | 128 = 255.
  assert(sparseTable.query(1, 3) ==
         14);  // Query range [1, 3], expect 2 | 4 | 8 = 14.
  std::cout << "All tests passed!" << std::endl;
  return 0;
}
