namespace SegmentTree {

template <typename T>
void update(std::vector<T>& tree, const int node, const int start,
            const int end, const int idx, T value) {
  if (start == end) {
    tree[node] ^= value;
    return;
  }
  int mid = (start + end) / 2;
  if (start <= idx && idx <= mid) {
    update(tree, 2 * node, start, mid, idx, value);
  } else {
    update(tree, 2 * node + 1, mid + 1, end, idx, value);
  }
  tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

template <typename T>
T query(const std::vector<T>& tree, const int node, const int start,
        const int end, const int L, const int R) {
  if (R < start || end < L) {
    return 0;  // XOR identity
  }
  if (L <= start && end <= R) {
    return tree[node];
  }
  int mid = (start + end) / 2;
  T leftXor = query(tree, 2 * node, start, mid, L, R);
  T rightXor = query(tree, 2 * node + 1, mid + 1, end, L, R);
  return leftXor ^ rightXor;
}
};