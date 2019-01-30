#include <bits/stdc++.h>
using namespace std;

const int N = 112345;
const int M = log2(N) + 5;

void lca_build(const auto &i, const auto &p, const auto &g, auto &depth, auto &dp) {
  dp[i][0] = p;
  depth[i] = depth[p] + 1;
  for (int j = 1; j < M; j += 1) {
    dp[i][j] = dp[dp[i][j - 1]][j - 1];
  }
  for (const auto &j: g[i]) {
    lca_build(j, i, g, depth, dp);
  }
}

int lca_query(const auto &x, const auto &y, const auto &depth, const auto &dp) {
  int i = x;
  int j = y;
  if (depth[i] < depth[j]) {
    swap(i, j);
  }
  int diff = depth[x] - depth[y];
  for (int k = M - 1; k >= 0; k -= 1) {
    if ((diff & (1 << k)) != 0) {
      i = dp[i][k];
    }
  }
  if (i == j) {
    return i;
  }
  for (int k = M - 1; k >= 0; k -= 1) {
    if (dp[i][k] != dp[j][k]) {
      i = dp[i][k];
      j = dp[j][k];
    }
  }
  return dp[i][0];
}

int main() {

}