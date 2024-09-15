#include <bits/stdc++.h>

namespace FenwickTree {

// Abstract helper class that defines the operations for the Fenwick Tree.
// The operations are defined through the 'getDefaultValue' and 'mergeValues'
// methods.
template <typename T>
class AbstractHelper {
 public:
  // Returns the default value used for the operations (e.g., 0 for sum, 0 for
  // XOR).
  virtual T getDefaultValue() const = 0;

  // Defines how two values are merged (e.g., addition for sum, XOR for xor).
  virtual T mergeValues(const T valueA, const T valueB) const = 0;
};

// Fenwick Tree class template that supports custom merge operations
// (like sum or XOR) using the provided helper class.
template <typename T>
class FenwickTree {
 public:
  // Constructor to initialize the Fenwick Tree with a given size and helper.
  FenwickTree(const int size, const AbstractHelper<T>& helper)
      : SIZE(size), HELPER(helper), tree(size, helper.getDefaultValue()) {}

  // Update the tree at index 'index' by merging the current value with 'value'.
  void update(int index, const T value) {
    // Update the tree nodes that cover the range of the index.
    for (; index < SIZE; index += index & -index) {
      tree[index] = HELPER.mergeValues(tree[index], value);
    }
  }

  // Query the tree for the cumulative value from 1 to 'index'.
  T query(int index) const {
    T result = HELPER.getDefaultValue();
    // Traverse the tree to compute the cumulative result.
    for (; index > 0; index -= index & -index) {
      result = HELPER.mergeValues(result, tree[index]);
    }
    return result;
  }

 private:
  const int SIZE;  // The size of the tree.
  const AbstractHelper<T>&
      HELPER;  // Reference to the helper for the merge operation.
  std::vector<T>
      tree;  // The Fenwick Tree (Binary Indexed Tree) data structure.
};

// Helper class that defines the sum operation for the Fenwick Tree.
template <typename T>
class SUM : public AbstractHelper<T> {
 public:
  // Merge two values using addition.
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA + valueB;
  }

  // Return the default value for sum, which is 0.
  T getDefaultValue() const override { return 0; }
};

// Helper class that defines the XOR operation for the Fenwick Tree.
template <typename T>
class XOR : public AbstractHelper<T> {
 public:
  // Merge two values using the XOR operation.
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA ^ valueB;
  }

  // Return the default value for XOR, which is 0.
  T getDefaultValue() const override { return 0; }
};
};  // namespace FenwickTree

// Test function to validate the SUM helper with the Fenwick Tree.
void testSUM() {
  FenwickTree::FenwickTree<int> tree(10, FenwickTree::SUM<int>());

  // Update the tree by adding 1 to each index from 1 to 9.
  for (int i = 1; i < 10; i += 1) {
    tree.update(i, 1);
  }

  // Query the cumulative sum at each index to ensure correctness.
  for (int i = 1; i < 10; i += 1) {
    assert(tree.query(i) == i);
  }

  std::cout << "Test SUM passed successfully!" << std::endl;
}

// Test function to validate the XOR helper with the Fenwick Tree.
void testXOR() {
  FenwickTree::FenwickTree<int> tree(10, FenwickTree::XOR<int>());

  // Update the tree by XORing 1 at each index from 1 to 9.
  for (int i = 1; i < 10; i += 1) {
    tree.update(i, 1);
  }

  // Test if the cumulative XOR queries return the expected results.
  assert(tree.query(1) == 1);  // XOR from 1 to 1: 1
  assert(tree.query(2) == 0);  // XOR from 1 to 2: 1 ^ 1 = 0
  assert(tree.query(3) == 1);  // XOR from 1 to 3: 1 ^ 1 ^ 1 = 1
  assert(tree.query(4) == 0);  // XOR from 1 to 4: 1 ^ 1 ^ 1 ^ 1 = 0
  assert(tree.query(8) == 0);  // All ones from 1 to 8 should XOR to 0
  assert(tree.query(9) == 1);  // Adding one more at index 9 gives 1

  // Additional test: Update index 5 with XOR of 8.
  tree.update(5, 8);
  // Validate the queries after the update.
  assert(tree.query(1) == 1);
  assert(tree.query(2) == 0);
  assert(tree.query(3) == 1);
  assert(tree.query(4) == 0);
  assert(tree.query(5) == 9);  // 1 ^ 8 = 9
  assert(tree.query(6) == 8);  // XOR from 1 to 6
  assert(tree.query(7) == 9);  // XOR from 1 to 7
  assert(tree.query(8) == 8);  // XOR from 1 to 8
  assert(tree.query(9) == 9);  // XOR from 1 to 9

  std::cout << "Test XOR passed successfully!" << std::endl;
}

int main() {
  testSUM();  // Run test for SUM Fenwick Tree.
  testXOR();  // Run test for XOR Fenwick Tree.
  std::cout << "All tests passed successfully!" << std::endl;
}
