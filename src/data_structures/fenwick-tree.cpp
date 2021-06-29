// Copyright (c) 2020 Gustavo Gardusi

#include <bits/stdc++.h>

template <typename T>
class FenwickTree {
 public:
  explicit FenwickTree(const int size) : accum(size, this->DEFAULT_VALUE) {}

  void resize(const int size) {
    if (size < 0) {
      throw std::invalid_argument("size should not be negative");
    }
    this->accum.resize(size);
  }

  void reset() { std::fill(accum.begin(), accum.end(), this->DEFAULT_VALUE); }

  void update(const int idx, const T value) {
    if (idx <= 0) {
      throw std::invalid_argument("idx should be positive");
    }
    if (idx >= static_cast<int>(accum.size())) {
      throw std::out_of_range("idx out of range");
    }
    for (int i = idx; i < static_cast<int>(accum.size()); i += i & (-i)) {
      this->accum[i] += value;
    }
  }

  T query(const int idx) const {
    if (idx >= static_cast<int>(this->accum.size())) {
      throw std::out_of_range("idx out of range");
    }
    T ans = 0;
    for (int i = idx; i > 0; i -= i & (-i)) {
      ans += this->accum[i];
    }
    return ans;
  }

 private:
  std::vector<T> accum;
  const T DEFAULT_VALUE = 0;
};
