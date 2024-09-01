#include <bits/stdc++.h>

struct Query {
  int L;
  int R;
  int index;
};

const int MAXN = 500000 + 5;

std::vector<int64_t> tree(4 * MAXN);

template <typename T>
void update(std::vector<T> &tree, const int node, const int start,
            const int end, const int idx, T value) {
  if (start == end) {
    tree[node] ^= val;
    return;
  }
  int mid = (start + end) / 2;
  if (start <= idx && idx <= mid) {
    update(2 * node, start, mid, idx, val);
  } else {
    update(2 * node + 1, mid + 1, end, idx, val);
  }
  tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

template <typename T>
T segmentTreeRangeQuery(std::vector<T> &tree, const int node, const int start,
                        const int end, const int L, const int R) {
  if (R < start || end < L) {
    return 0;
  }
  if (L <= start && end <= R) {
    return tree[node];
  }
  int mid = (start + end) / 2;
  T leftXor = query(2 * node, start, mid, L, R);
  T rightXor = query(2 * node + 1, mid + 1, end, L, R);
  return leftXor ^ rightXor;
}

void solve() {
  int N, Q;
  std::cin >> N >> Q;
  std::vector<int64_t> v(N + 1);
  std::vector<int64_t> accumXOR(N + 1, 0);
  for (int i = 1; i <= N; i++) {
    std::cin >> v[i];
    accumXOR[i] = accumXOR[i - 1] ^ v[i];
  }

  vector<Query> queries(Q);
  vector<int64_t> results(Q);
  for (int i = 0; i < Q; i++) {
    cin >> queries[i].L >> queries[i].R;
    queries[i].index = i;
  }

  sort(queries.begin(), queries.end(),
       [](const Query &a, const Query &b) { return a.R < b.R; });

  vector<int64_t> uniqueElements(v.begin() + 1, v.end());
  sort(uniqueElements.begin(), uniqueElements.end());
  uniqueElements.erase(
      std::unique(uniqueElements.begin(), uniqueElements.end()),
      uniqueElements.end());
  std::unordered_map<int, int> compressed;
  for (int i = 0; i < uniqueElements.size(); i++) {
    compressed[uniqueElements[i]] = i + 1;
  }
  std::vector<int> lastOccurrence(MAXN);
  std::fill(lastOccurrenceOfElement.begin(), lastOccurrenceOfElement.end(), -1);
  int currentR = 0;
  for (const auto &q : queries) {
    while (currentR < q.R) {
      currentR++;
      int compressedIdx = compressed[v[currentR]];
      if (lastOccurrence[compressedIdx] != -1) {
        update(1, 1, uniqueElements.size(), lastOccurrence[compressedIdx],
               v[currentR]);
      }
      update(1, 1, uniqueElements.size(), currentR, v[currentR]);
      lastOccurrence[compressedIdx] = currentR;
    }

    int64_t segmentTreeXOR = query(1, 1, uniqueElements.size(), q.L, q.R);
    int64_t resultXOR = accumXOR[q.R] ^ accumXOR[q.L - 1];
    std::cout << "q.index: " << q.index << ", uniqueXOR: " << segmentTreeXOR
              << ", resultXOR: " << resultXOR << std::endl;
    results[q.index] = resultXOR ^ segmentTreeXOR;
  }

  for (int i = 0; i < Q; i++) {
    cout << results[i] << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  solve();
  return 0;
}