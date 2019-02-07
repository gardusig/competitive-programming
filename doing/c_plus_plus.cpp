#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000021;

void dfs0(const auto &i, const auto &g, auto &used, auto &st) {
  used[i] = true;
  for (const auto &j: g[i]) {
    if (used[j] == false) {
      dfs0(j, g, used, st);
    }
  }
  st.push(i);
}

void dfs1(const auto &i, const auto &g, auto &used, const auto &idx, auto &components) {
  used[i] = true;
  components[i] = idx;
  for (const auto &j: g[i]) {
    if (used[j] == false) {
      dfs1(j, g, used, idx, components);
    }
  }
}

vector< int > build_components(const auto &n, const auto &g, const auto &t) {
  stack< int > st;
  vector< bool > used(n, false);
  for (int i = 0; i < n; i += 1) {
    if (used[i] == false) {
      dfs0(i, g, used, st);
    }
  }
  int idx = 0;
  vector< int > components(n);
  used = vector< bool >(n, false);
  while (st.empty() == false) {
    int i = st.top();
    st.pop();
    if (used[i] == false) {
      dfs1(i, t, used, idx, components);
      idx += 1;
    }
  }
  return components;
}

vector< int > join(const auto &a, const auto &b, const auto &k) {
  vector< int > ans;
  for (int i = 0, j = 0; int(ans.size()) < k;) {
    bool kappa = (i < int(a.size()));
    bool keepo = (j < int(b.size()));
    if (kappa == true and keepo == true) {
      if (a[i] < b[j]) {
        ans.push_back(a[i]);
        i += 1;
      } else {
        ans.push_back(b[j]);
        j += 1;
      }
    } else if (kappa == true) {
      ans.push_back(a[i]);
      i += 1;
    } else if (keepo == true) {
      ans.push_back(b[j]);
      j += 1;
    } else {
      break;
    }
  }
  return ans;
}

void build_worst(const auto &i, const auto &k, const auto &g, const auto &v, auto &worst) {
  for (const auto &j: g[i]) {
    build_worst(j, k, g, v, worst);
    worst[i] = join(worst[i], worst[j], k);
  }
}

long long int solve(const auto &i, const auto &k, const auto &g, const auto &v, const auto &worst, auto &dp) {
  if (dp[i][k] != -1) {
    return dp[i][k];
  }
  int lo = 0, hi = min(k, int(v[i].size()) - 1);
  while (lo <= hi) {
    const auto mid = (lo + hi) / 2;
    if (v[i][mid] < worst[i][mid]) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  int qtd = hi + 1;
  long long int current = 1LL * (int(v[i].size()) - qtd) * v[i][qtd];
  long long int ans = current;
  for (const auto &j: g[i]) {
    ans = max(ans, solve(j, k - qtd, g, v, worst, dp) + current);
  }
  return dp[i][k] = ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, m, k;
    cin >> n >> m >> k;
    vector< int > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    vector< vector< int > > g(n), t(n);
    vector< pair< int, int > > edges;
    for (int i = 0; i < m; i += 1) {
      int x, y;
      cin >> x >> y;
      x -= 1;
      y -= 1;
      g[x].push_back(y);
      t[y].push_back(x);
      edges.push_back({x, y});
    }
    auto components = build_components(n, g, t);
    vector< int > degree(n, 0);
    vector< vector< int > > new_g(n);
    for (int i = 0; i < m; i += 1) {
      int x = edges[i].first;
      int y = edges[i].second;
      if (components[x] != components[y]) {
        degree[components[y]] += 1;
        new_g[components[x]].push_back(components[y]);
      }
    }
    vector< vector< int > > new_v(n);
    for (int i = 0; i < n; i += 1) {
      new_v[components[i]].push_back(v[i]);
    }
    for (int i = 0; i < n; i += 1) {
      sort(new_v[i].begin(), new_v[i].end());
    }
    vector< vector< int > > worst(n + 5, vector< int >(k + 5));
    for (int i = 0; i < n; i += 1) {
      build_worst(i, k, new_g, new_v, worst);
    }
    long long int ans = 0;
    vector< vector< long long int > > dp(n + 5, vector< long long int >(k + 5, -1));
    for (int i = 0; i < n; i += 1) {
      ans = max(ans, solve(i, k, new_g, new_v, worst, dp));
    }
    cout << ans % MOD << '\n';
  }
  return 0;
}