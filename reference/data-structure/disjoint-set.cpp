#include <bits/stdc++.h>

namespace dsu {
class DisjointSet {
 private:
  std::vector<int> parent, size;

 public:
  DisjointSet(int arraySize) : parent(arraySize), size(arraySize, 1) {
    for (int i = 0; i < arraySize; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (x != parent[x]) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (size[x] < size[y]) {
      std::swap(x, y);
    }
    parent[y] = x;
    size[x] += size[y];
  }

  bool isConnected(int x, int y) { return find(x) == find(y); }
};
}  // namespace dsu

int main() {
  dsu::DisjointSet ds(10);
  for (int i = 0; i < 10; i += 1) {
    assert(ds.isConnected(i, i) == true);
  }
  assert(ds.isConnected(0, 1) == false);
  assert(ds.isConnected(0, 2) == false);
  assert(ds.isConnected(0, 3) == false);
  ds.unite(0, 1);
  assert(ds.isConnected(0, 1) == true);
  assert(ds.isConnected(0, 2) == false);
  assert(ds.isConnected(0, 3) == false);
  ds.unite(0, 2);
  assert(ds.isConnected(0, 1) == true);
  assert(ds.isConnected(0, 2) == true);
  assert(ds.isConnected(1, 2) == true);
  assert(ds.isConnected(0, 3) == false);
  assert(ds.isConnected(1, 3) == false);
  return 0;
}
