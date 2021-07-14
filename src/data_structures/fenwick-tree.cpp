// Copyright (c) 2020 Gustavo Gardusi

#include <bits/stdc++.h>

template <typename T>
class FenwickTree {
 public:
  explicit FenwickTree(const int size);

  void clear();
  void resize(const int size);

  T query(const int idx) const;
  void update(const int idx, const T value);

 private:
  std::vector<T> accum;

  static const T DEFAULT_VALUE;
};

template <typename T>
const T FenwickTree<T>::DEFAULT_VALUE = 0;

template <typename T>
FenwickTree<T>::FenwickTree(const int size)
    : accum(size, FenwickTree::DEFAULT_VALUE) {}

template <typename T>
void FenwickTree<T>::resize(const int size) {
  if (size < 0) {
    assert(false);
  }
  this->accum.resize(size);
}

template <typename T>
void FenwickTree<T>::clear() {
  std::fill(accum.begin(), accum.end(), FenwickTree::DEFAULT_VALUE);
}

template <typename T>
void FenwickTree<T>::update(const int idx, const T value) {
  if (idx <= 0) {
    assert(false);
  }
  if (idx >= static_cast<int>(accum.size())) {
    assert(false);
  }
  for (int i = idx; i < static_cast<int>(accum.size()); i += i & (-i)) {
    this->accum[i] += value;
  }
}

template <typename T>
T FenwickTree<T>::query(const int idx) const {
  if (idx >= static_cast<int>(this->accum.size())) {
    assert(false);
  }
  T ans = 0;
  for (int i = idx; i > 0; i -= i & (-i)) {
    ans += this->accum[i];
  }
  return ans;
}
