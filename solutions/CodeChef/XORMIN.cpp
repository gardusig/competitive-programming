#include <bits/stdc++.h>
using namespace std;

const int N = 5123;
const int MAX_BITS = 20;

class node {
public:
  int vertex;
  node *nxt[2];

  node() {
    this->vertex = INT_MAX;
    for (int i = 0; i < 2; i += 1) {
      this->nxt[i] = NULL;
    }
  }

  void insert(const auto &mask, const auto &bit, const auto &vertex) {
    this->vertex = min(this->vertex, vertex);
    if (bit < 0) {
      return;
    }
    int nxt_bit = (mask & (1 << bit)) ? 1 : 0;
    if (this->nxt[nxt_bit] == NULL) {
      this->nxt[nxt_bit] = new node();
    }
    this->nxt[nxt_bit]->insert(mask, bit - 1, vertex);
  }

  pair< int, int > ask(const auto &mask, const auto &bit, const auto &ans) {
    if (bit < 0) {
      return {ans, this->vertex};
    }
    int nxt_bit = (mask & (1 << bit)) ? 1 : 0;
    if (this->nxt[nxt_bit ^ 1] == NULL) {
      return this->nxt[nxt_bit]->ask(mask, bit - 1, ans);
    }
    return this->nxt[nxt_bit ^ 1]->ask(mask, bit - 1, ans | (1 << bit));
  }
};

int w[N];
node *trie[N];
vector< int > g[N];

vector< int > build(const auto &i, const auto &p) {
  vector< int > v;
  v.push_back(i);
  for (const auto &j: g[i]) {
    if (j == p) {
      continue;
    }
    for (const auto &k: build(j, i)) {
      v.push_back(k);
    }
  }
  for (const auto &j: v) {
    trie[i]->insert(w[j], MAX_BITS - 1, j + 1);
  }
  return v;
}

void scanint(int &x) {
  x = 0;
  register int c = getchar_unlocked();
  for (; c < 48 or c > 57; c = getchar_unlocked());
  for (; c > 47 and c < 58; c = getchar_unlocked()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
}

int main() {
  int t;
  scanint(t);
  while (t-- > 0) {
    int n, q;
    scanint(n);
    scanint(q);
    assert(n < N);
    for (int i = 0; i < n; i += 1) {
      scanint(w[i]);
      g[i].clear();
    }
    for (int i = 1; i < n; i += 1) {
      int x, y;
      scanint(x);
      scanint(y);
      x -= 1;
      y -= 1;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    for (int i = 0; i < n; i += 1) {
      trie[i] = new node();
    }
    build(0, -1);
    int ans = 0;
    int vertex = 0;
    while (q-- > 0) {
      int a, b;
      scanint(a);
      scanint(b);
      int current_vertex = vertex ^ a;
      int k = ans ^ b;
      auto current_ans = trie[current_vertex - 1]->ask(k, MAX_BITS - 1, 0);
      ans = current_ans.first;
      vertex = current_ans.second;
      printf("%d %d\n", vertex, ans);
    }
  }
  return 0;
}