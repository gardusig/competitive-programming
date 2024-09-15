#include <bits/stdc++.h>

namespace SegmentTree {

// Abstract helper class to define the operations for the Segment Tree.
// Includes methods for default value, merging two values, and handling lazy
// propagation.
template <typename T>
class AbstractHelper {
 public:
  // Returns the default value for the segment tree (e.g., 0 for sum, 0 for
  // XOR).
  virtual T getDefaultValue() const = 0;

  // Merges two values (e.g., addition for sum, XOR for xor).
  virtual T mergeValues(const T valueA, const T valueB) const = 0;

  // Handles the propagation of lazy updates in the range [L, R].
  virtual T mergeValuesInRange(const T currentValue, const T lazyValue,
                               const int L, const int R) const = 0;
};

// Segment tree class that supports range updates and lazy propagation.
// Allows flexible operations via the AbstractHelper interface.
template <typename T>
class SegmentTree {
 public:
  // Constructor to initialize the segment tree with a given size and helper.
  SegmentTree(const int size, const AbstractHelper<T>& helper)
      : SIZE(size),
        HELPER(helper),
        tree(4 * size,
             helper.getDefaultValue()),  // Allocate space for tree nodes.
        lazy(4 * size, helper.getDefaultValue()) {
  }  // Allocate space for lazy propagation.

  // Public method to update the range [L, R] with a value.
  void updateRange(const int L, const int R, const T value) {
    updateRange(1, 0, SIZE - 1, L, R, value);
  }

  // Public method to query the range [L, R] for the merged result.
  T query(const int L, const int R) { return query(1, 0, SIZE - 1, L, R); }

 private:
  // Recursive method to handle range updates, applying lazy propagation.
  void updateRange(const int treeIndex, const int start, const int end,
                   const int rangeL, const int rangeR, const T updateValue) {
    propagate(treeIndex, start,
              end);  // Ensure all pending updates are applied.

    // Return if the current segment is outside the update range.
    if (start > rangeR || end < rangeL) {
      return;
    }

    // If the current segment is completely within the update range.
    if (start >= rangeL && end <= rangeR) {
      lazy[treeIndex] = HELPER.mergeValues(lazy[treeIndex],
                                           updateValue);  // Store the update.
      propagate(treeIndex, start, end);  // Apply the update using propagation.
      return;
    }

    // Recursively update the left and right children.
    int mid = (start + end) / 2;
    updateRange(2 * treeIndex, start, mid, rangeL, rangeR, updateValue);
    updateRange(2 * treeIndex + 1, mid + 1, end, rangeL, rangeR, updateValue);

    // Recompute the current node's value based on the children's values.
    tree[treeIndex] =
        HELPER.mergeValues(tree[2 * treeIndex], tree[2 * treeIndex + 1]);
  }

  // Recursive method to handle range queries.
  T query(const int treeIndex, const int start, const int end, const int rangeL,
          const int rangeR) {
    propagate(treeIndex, start, end);  // Apply pending updates before querying.

    // Return default value if the current segment is outside the query range.
    if (start > rangeR || end < rangeL) {
      return HELPER.getDefaultValue();
    }

    // If the current segment is completely within the query range.
    if (start >= rangeL && end <= rangeR) {
      return tree[treeIndex];
    }

    // Query the left and right children recursively.
    int mid = (start + end) / 2;
    T leftResult = query(2 * treeIndex, start, mid, rangeL, rangeR);
    T rightResult = query(2 * treeIndex + 1, mid + 1, end, rangeL, rangeR);

    // Return the merged result from both children.
    return HELPER.mergeValues(leftResult, rightResult);
  }

  // Method to propagate lazy updates to children nodes.
  void propagate(int treeIndex, int start, int end) {
    // Only propagate if there's a pending update.
    if (lazy[treeIndex] == HELPER.getDefaultValue()) {
      return;
    }

    // Apply the lazy value to the current node for the entire range [start,
    // end].
    tree[treeIndex] =
        HELPER.mergeValuesInRange(tree[treeIndex], lazy[treeIndex], start, end);

    // If not a leaf node, propagate the lazy value to the children.
    if (start != end) {
      lazy[2 * treeIndex] =
          HELPER.mergeValues(lazy[2 * treeIndex], lazy[treeIndex]);
      lazy[2 * treeIndex + 1] =
          HELPER.mergeValues(lazy[2 * treeIndex + 1], lazy[treeIndex]);
    }

    // Clear the lazy value for the current node.
    lazy[treeIndex] = HELPER.getDefaultValue();
  }

  const int SIZE;  // Size of the segment tree.
  const AbstractHelper<T>&
      HELPER;  // Reference to the helper for the merge operations.

  std::vector<T> tree;  // Segment tree data structure.
  std::vector<T> lazy;  // Lazy propagation array.
};

// Helper class for SUM operations in the segment tree.
template <typename T>
class SUM : public AbstractHelper<T> {
 public:
  // Merge two values using addition.
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA + valueB;
  }

  // Handle lazy propagation by applying the update to the entire range.
  T mergeValuesInRange(const T currentValue, const T lazyValue, const int L,
                       const int R) const override {
    return currentValue +
           (lazyValue *
            (R - L + 1));  // Update the current value based on range size.
  }

  // Return the default value for sum operations (0).
  T getDefaultValue() const override { return 0; }
};

// Helper class for XOR operations in the segment tree.
template <typename T>
class XOR : public AbstractHelper<T> {
 public:
  // Merge two values using XOR.
  T mergeValues(const T valueA, const T valueB) const override {
    return valueA ^ valueB;
  }

  // Handle lazy propagation for XOR over a range.
  T mergeValuesInRange(const T currentValue, const T lazyValue, const int L,
                       const int R) const override {
    // XOR propagation only affects ranges with an odd length.
    return currentValue ^ (lazyValue * ((R - L + 1) & 1));
  }

  // Return the default value for XOR operations (0).
  T getDefaultValue() const override { return 0; }
};
}  // namespace SegmentTree

// Test function for SUM operations in the Segment Tree.
void testSUM() {
  SegmentTree::SegmentTree<int> tree(10, SegmentTree::SUM<int>());

  tree.updateRange(2, 4, 5);       // Update range [2, 4] with 5.
  assert(tree.query(0, 9) == 15);  // Query range [0, 9], expecting 15.

  // Additional tests to ensure the correctness of updates and queries.
  assert(tree.query(2, 4) == 15);
  assert(tree.query(4, 5) == 5);
  assert(tree.query(5, 5) == 0);
  assert(tree.query(4, 4) == 5);
  assert(tree.query(3, 4) == 10);
  assert(tree.query(3, 3) == 5);

  tree.updateRange(0, 3, 6);  // Update range [0, 3] with 6.
  assert(tree.query(0, 0) == 6);
  assert(tree.query(0, 1) == 12);
  assert(tree.query(1, 1) == 6);
  assert(tree.query(2, 2) == 11);
  assert(tree.query(2, 3) == 22);

  tree.updateRange(2, 3, -5);  // Update range [2, 3] with -5.
  assert(tree.query(3, 3) == 6);
  assert(tree.query(0, 9) == 29);

  std::cout << "Test SUM passed successfully!" << std::endl;
}

// Test function for XOR operations in the Segment Tree.
void testXOR() {
  SegmentTree::SegmentTree<int> tree(10, SegmentTree::XOR<int>());

  tree.updateRange(0, 9, 1);      // Update range [0, 9] with 1.
  assert(tree.query(0, 9) == 0);  // Query range [0, 9], expecting 0.

  // Further checks for XOR correctness.
  assert(tree.query(0, 0) == 1);
  assert(tree.query(0, 1) == 0);
  assert(tree.query(0, 2) == 1);

  tree.updateRange(0, 9, 1);
  assert(tree.query(0, 9) == 0);

  tree.updateRange(0, 9, 16);
  assert(tree.query(0, 9) == 0);

  std::cout << "Test XOR passed successfully!" << std::endl;
}

int main() {
  testSUM();  // Run the test for SUM operations.
  testXOR();  // Run the test for XOR operations.
  std::cout << "All tests passed successfully!" << std::endl;
  return 0;
}
