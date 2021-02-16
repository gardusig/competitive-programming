#include <stdexcept>
#include <vector>

template <typename T>
class FenwickTree {
 public:
  FenwickTree();
  FenwickTree(const int size);

  void resize(const int size);
  void reset();

  void update(const int idx, const T value);

  T query(const int idx) const;

 private:
  std::vector<T> accum;
  const T DEFAULT_VALUE = 0;
};

template <typename T>
FenwickTree<T>::FenwickTree() : FenwickTree(0) {}

template <typename T>
FenwickTree<T>::FenwickTree(const int size)
    : accum(size, this->DEFAULT_VALUE) {}

template <typename T>
void FenwickTree<T>::reset() {
  std::fill(accum.begin(), accum.end(), this->DEFAULT_VALUE);
}

template <typename T>
void FenwickTree<T>::resize(const int size) {
  if (size < 0) {
    throw std::invalid_argument("size should not be negative");
  }
  this->accum.resize(size);
}

template <typename T>
void FenwickTree<T>::update(const int idx, const T value) {
  if (idx <= 0) {
    throw std::invalid_argument("idx should be positive");
  }
  for (int i = idx; i < int(accum.size()); i += i & (-i)) {
    this->accum[i] += value;
  }
}

template <typename T>
T FenwickTree<T>::query(const int idx) const {
  if (idx >= this->accum.size()) {
    throw std::out_of_range("idx out of range");
  }
  T ans = 0;
  for (int i = idx; i > 0; i -= i & (-i)) {
    ans += this->accum[i];
  }
  return ans;
}