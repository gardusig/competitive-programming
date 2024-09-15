#include <bits/stdc++.h>

namespace dsu {
// Disjoint Set Union (DSU) class implementation using path compression and
// union by size.
class DisjointSet {
 private:
  std::vector<int> parent, size;  // 'parent' stores the representative of each
                                  // set, 'size' stores the size of each set.

 public:
  // Constructor to initialize 'parent' and 'size' arrays for sets from 0 to
  // arraySize-1.
  DisjointSet(int arraySize) : parent(arraySize), size(arraySize, 1) {
    // Initially, each element is its own parent (self-loop), forming
    // single-element sets.
    for (int i = 0; i < arraySize; ++i) {
      parent[i] = i;
    }
  }

  // Find function with path compression to optimize future queries.
  int find(int x) {
    // If 'x' is not its own parent, recursively find the representative and
    // compress the path.
    if (x != parent[x]) {
      parent[x] = find(parent[x]);
    }
    return parent[x];  // Return the representative (root) of the set containing
                       // 'x'.
  }

  // Union by size: combine sets containing 'x' and 'y' by connecting the
  // smaller tree under the larger tree.
  void unite(int x, int y) {
    x = find(x);  // Find the root of the set containing 'x'.
    y = find(y);  // Find the root of the set containing 'y'.
    if (x == y) {
      return;  // If 'x' and 'y' are already in the same set, do nothing.
    }
    // Ensure that the larger set becomes the parent.
    if (size[x] < size[y]) {
      std::swap(x, y);
    }
    parent[y] = x;       // Make 'x' the new root of the combined set.
    size[x] += size[y];  // Update the size of the new root.
  }

  // Check if 'x' and 'y' are in the same set.
  bool isConnected(int x, int y) { return find(x) == find(y); }
};
}  // namespace dsu

int main() {
  dsu::DisjointSet ds(10);  // Initialize DSU with 10 elements (from 0 to 9).

  // Test cases to validate the correctness of the DSU implementation.
  // Initially, each element is its own set, so 'isConnected(i, i)' should
  // always return true.
  for (int i = 0; i < 10; i += 1) {
    assert(ds.isConnected(i, i) == true);
  }

  // Elements are in separate sets initially, so 'isConnected' between different
  // elements should return false.
  assert(ds.isConnected(0, 1) == false);
  assert(ds.isConnected(0, 2) == false);
  assert(ds.isConnected(0, 3) == false);

  // Unite elements 0 and 1, so they should now be in the same set.
  ds.unite(0, 1);
  assert(ds.isConnected(0, 1) == true);

  // Elements 0 and 2 are still in separate sets.
  assert(ds.isConnected(0, 2) == false);
  assert(ds.isConnected(0, 3) == false);

  // Unite elements 0 and 2, so now 0, 1, and 2 should all be in the same set.
  ds.unite(0, 2);
  assert(ds.isConnected(0, 1) == true);
  assert(ds.isConnected(0, 2) == true);
  assert(ds.isConnected(1, 2) == true);

  // Element 3 is still in its own set.
  assert(ds.isConnected(0, 3) == false);
  assert(ds.isConnected(1, 3) == false);

  return 0;  // Program ends successfully.
}
