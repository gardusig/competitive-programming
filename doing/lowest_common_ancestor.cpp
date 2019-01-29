#include < bits/stdc++.h >

void build_lca(const auto &i, const auto &p, const auto &g, auto &depth, auto &dp) {
  dp[i][0] = p;
  depth[i] = depth[p] + 1;
  for (int j = 1; j < M; j += 1) {
    dp[i][j] = dp[dp[i][j - 1]][j - 1];
  }
  for (const auto &j: g[i]) {
    build_lca(j, i, g, depth, dp);
  }
}

int main() {

}