#include <bits/stdc++.h>

namespace SegmentTree {

template <typename T>
class AbstractHelper {
 public:
  virtual T getDefaultValue() const = 0;
  virtual T mergeValues(const T valueA, const T valueB) const = 0;
  virtual T mergeValuesInRange(const T currentValue, const T lazyValue,
                               const int L, const int R) const = 0;
};

template <typename T>
class SegmentTree {
 public:
  SegmentTree(const int size, const AbstractHelper<T>& helper)
      : SIZE(size),
        HELPER(helper),
        tree(4 * size, helper.getDefaultValue()),
        lazy(4 * size, helper.getDefaultValue()) {}

  void updateRange(const int L, const int R, const T value) {
    updateRange(1, 0, SIZE - 1, L, R, value);
  }

  T query(const int L, const int R) { return query(1, 0, SIZE - 1, L, R); }

 private:
  void updateRange(const int treeIndex, const int start, const int end,
                   const int rangeL, const int rangeR, const T updateValue) {
    propagate(treeIndex, start, end);
    if (start > rangeR || end < rangeL) {
      return;
    }
    if (start >= rangeL && end <= rangeR) {
      lazy[treeIndex] = HELPER.mergeValues(lazy[treeIndex], updateValue);
      propagate(treeIndex, start, end);
      return;
    }
    int mid = (start + end) / 2;
    updateRange(2 * treeIndex, start, mid, rangeL, rangeR, updateValue);
    updateRange(2 * treeIndex + 1, mid + 1, end, rangeL, rangeR, updateValue);
    tree[treeIndex] =
        HELPER.mergeValues(tree[2 * treeIndex], tree[2 * treeIndex + 1]);
  }

  T query(const int treeIndex, const int start, const int end, const int rangeL,
          const int rangeR) {
    propagate(treeIndex, start, end);
    if (start > rangeR || end < rangeL) {
      return HELPER.getDefaultValue();
    }
    if (start >= rangeL && end <= rangeR) {
      return tree[treeIndex];
    }
    int mid = (start + end) / 2;
    T leftResult = query(2 * treeIndex, start, mid, rangeL, rangeR);
    T rightResult = query(2 * treeIndex + 1, mid + 1, end, rangeL, rangeR);
    return HELPER.mergeValues(leftResult, rightResult);
  }

  void propagate(int treeIndex, int start, int end) {
    if (lazy[treeIndex] == HELPER.getDefaultValue()) {
      return;
    }
    tree[treeIndex] =
        HELPER.mergeValuesInRange(tree[treeIndex], lazy[treeIndex], start, end);
    if (start != end) {
      int mid = (start + end) / 2;
      lazy[2 * treeIndex] =
          HELPER.mergeValues(lazy[2 * treeIndex], lazy[treeIndex]);
      lazy[2 * treeIndex + 1] =
          HELPER.mergeValues(lazy[2 * treeIndex + 1], lazy[treeIndex]);
    }
    lazy[treeIndex] = HELPER.getDefaultValue();
  }

  const int SIZE;
  const AbstractHelper<T>& HELPER;

  std::vector<T> tree;
  std::vector<T> lazy;
};

template <typename T>
class SUM : public AbstractHelper<T> {
 public:
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA + valueB;
  }

  T mergeValuesInRange(const T currentValue, const T lazyValue, const int L,
                       const int R) const override {
    return currentValue + (lazyValue * (R - L + 1));
  }

  T getDefaultValue() const override { return 0; }
};

template <typename T>
class XOR : public AbstractHelper<T> {
 public:
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA ^ valueB;
  }

  T mergeValuesInRange(const T currentValue, const T lazyValue, const int L,
                       const int R) const override {
    return currentValue ^ (lazyValue * ((R - L + 1) & 1));
  }

  T getDefaultValue() const override { return 0; }
};
}  // namespace SegmentTree

void testSUM() {
  SegmentTree::SegmentTree<int> tree(10, SegmentTree::SUM<int>());
  tree.updateRange(2, 4, 5);
  assert(tree.query(0, 9) == 15);
  assert(tree.query(2, 4) == 15);
  assert(tree.query(4, 5) == 5);
  assert(tree.query(5, 5) == 0);
  assert(tree.query(4, 4) == 5);
  assert(tree.query(3, 4) == 10);
  assert(tree.query(3, 3) == 5);
  tree.updateRange(0, 3, 6);
  assert(tree.query(0, 0) == 6);
  assert(tree.query(0, 1) == 12);
  assert(tree.query(1, 1) == 6);
  assert(tree.query(2, 2) == 11);
  assert(tree.query(2, 3) == 22);
  assert(tree.query(3, 3) == 11);
  tree.updateRange(2, 3, -5);
  assert(tree.query(3, 3) == 6);
  assert(tree.query(0, 3) == 24);
  assert(tree.query(4, 4) == 5);
  assert(tree.query(0, 9) == 29);
  std::cout << "Test SUM passed successfully!" << std::endl;
}

void testXOR() {
  SegmentTree::SegmentTree<int> tree(10, SegmentTree::XOR<int>());
  tree.updateRange(0, 9, 1);
  assert(tree.query(0, 9) == 0);
  assert(tree.query(0, 0) == 1);
  assert(tree.query(0, 1) == 0);
  assert(tree.query(0, 2) == 1);
  tree.updateRange(0, 9, 1);
  assert(tree.query(0, 9) == 0);
  assert(tree.query(0, 0) == 0);
  assert(tree.query(0, 1) == 0);
  assert(tree.query(0, 2) == 0);
  tree.updateRange(0, 9, 16);
  assert(tree.query(0, 9) == 0);
  assert(tree.query(0, 0) == 16);
  assert(tree.query(0, 1) == 0);
  assert(tree.query(0, 2) == 16);
  std::cout << "Test XOR passed successfully!" << std::endl;
}

int main() {
  testSUM();
  testXOR();
  std::cout << "All tests passed successfully!" << std::endl;
  return 0;
}