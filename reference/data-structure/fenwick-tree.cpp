#include <bits/stdc++.h>

namespace FenwickTree {

template <typename T>
class AbstractHelper {
 public:
  virtual T getDefaultValue() const = 0;
  virtual T mergeValues(const T valueA, const T valueB) const = 0;
};

template <typename T>
class FenwickTree {
 public:
  FenwickTree(const int size, const AbstractHelper<T>& helper)
      : SIZE(size), HELPER(helper), tree(size, helper.getDefaultValue()) {}

  void update(int index, const T value) {
    for (; index < SIZE; index += index & -index) {
      tree[index] = HELPER.mergeValues(tree[index], value);
    }
  }

  T query(int index) const {
    T result = HELPER.getDefaultValue();
    for (; index > 0; index -= index & -index) {
      result = HELPER.mergeValues(result, tree[index]);
    }
    return result;
  }

 private:
  const int SIZE;
  const AbstractHelper<T>& HELPER;

  std::vector<T> tree;
};

template <typename T>
class SUM : public AbstractHelper<T> {
 public:
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA + valueB;
  }

  T getDefaultValue() const override { return 0; }
};

template <typename T>
class XOR : public AbstractHelper<T> {
 public:
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA ^ valueB;
  }

  T getDefaultValue() const override { return 0; }
};
};  // namespace FenwickTree

void testSUM() {
  FenwickTree::FenwickTree<int> tree(10, FenwickTree::SUM<int>());
  for (int i = 1; i < 10; i += 1) {
    tree.update(i, 1);
  }
  for (int i = 1; i < 10; i += 1) {
    assert(tree.query(i) == i);
  }
  std::cout << "Test SUM passed successfully!" << std::endl;
}

void testXOR() {
  FenwickTree::FenwickTree<int> tree(10, FenwickTree::XOR<int>());
  for (int i = 1; i < 10; i += 1) {
    tree.update(i, 1);
  }
  assert(tree.query(1) == 1);
  assert(tree.query(2) == 0);
  assert(tree.query(3) == 1);
  assert(tree.query(4) == 0);
  assert(tree.query(8) == 0);
  assert(tree.query(9) == 1);
  tree.update(5, 8);
  assert(tree.query(1) == 1);
  assert(tree.query(2) == 0);
  assert(tree.query(3) == 1);
  assert(tree.query(4) == 0);
  assert(tree.query(5) == 9);
  assert(tree.query(6) == 8);
  assert(tree.query(7) == 9);
  assert(tree.query(8) == 8);
  assert(tree.query(9) == 9);
  std::cout << "Test XOR passed successfully!" << std::endl;
}

int main() {
  testSUM();
  testXOR();
  std::cout << "All tests passed successfully!" << std::endl;
}