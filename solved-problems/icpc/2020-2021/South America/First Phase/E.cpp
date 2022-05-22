#include <bits/stdc++.h>

class FenwickTree {
 public:
  FenwickTree(const int size) : v(size, 0) {}

  void update(const int idx, const int value) {
    for (int i = idx; i < v.size(); i += i & -i) {
      v[i] += value;
    }
  }

  int query(const int idx) const {
    int ans = 0;
    for (int i = idx; i > 0; i -= i & -i) {
      ans += v[i];
    }
    return ans;
  }

 private:
  std::vector<int> v;
};

const int MAX_SIZE = 112345;
const int MAX_SIZE_LOG = 20;

int N, M;
int age[MAX_SIZE];
std::vector<int> g[MAX_SIZE];
int lca[MAX_SIZE][MAX_SIZE_LOG];
std::vector<int> to_add[MAX_SIZE];
FenwickTree bit(MAX_SIZE);
int answer[MAX_SIZE];

void build_lca(const int i, const int p) {
  lca[i][0] = p;
  for (int j = 1; j < MAX_SIZE_LOG; j += 1) {
    lca[i][j] = lca[lca[i][j - 1]][j - 1];
  }
  for (const int k : g[i]) {
    if (k == p) {
      continue;
    }
    build_lca(k, i);
  }
}

void add(const int i, const int L, const int R) {
  for (int k = MAX_SIZE_LOG - 1; k >= 0; k -= 1) {
    const int vertex = lca[i][k];
    if (vertex != i and age[vertex] <= R) {
      add(vertex, L, R);
      return;
    }
  }
  to_add[i].push_back(L);
}

void dfs(const int i, const int p) {
  for (const int value : to_add[i]) {
    bit.update(value, +1);
  }
  answer[i] = bit.query(age[i]);
  for (const int k : g[i]) {
    if (k == p) {
      continue;
    }
    dfs(k, i);
  }
  for (const int value : to_add[i]) {
    bit.update(value, -1);
  }
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; i += 1) {
    int parent;
    scanf("%d %d", &age[i], &parent);
    parent -= 1;
    g[i].push_back(parent);
    g[parent].push_back(i);
  }
  build_lca(0, 0);
  for (int i = 0; i < M; i += 1) {
    int vertex, L, R;
    scanf("%d %d %d", &vertex, &L, &R);
    add(vertex - 1, L, R);
  }
  dfs(0, 0);
  for (int i = 0; i < N; i += 1) {
    printf("%d ", answer[i]);
  }
  puts("");
  return 0;
}
