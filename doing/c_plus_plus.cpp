#include <bits/stdc++.h>
using namespace std;

std::mt19937 rng(int(std::chrono::steady_clock::now().time_since_epoch().count()));

const int MOD = 1000000007;

vector< int > build(const auto &n, const auto &x0, const auto &y0, const auto &c, const auto &d, const auto &ex, const auto &ey, const auto &f) {
  vector< int > v(n), x(n), y(n);
  x[0] = x0;
  y[0] = y0;
  v[0] = (x[0] + y[0]) % f;
  for (int i = 1; i < n; i += 1) {
    x[i] = ((1LL * c * x[i - 1]) + (1LL * d * y[i - 1]) + ex) % f;
    y[i] = ((1LL * d * x[i - 1]) + (1LL * c * y[i - 1]) + ey) % f;
    v[i] = (x[i] + y[i]) % f;
  }
  return v;
}

int exp(const auto &n, const auto &k) {
  if (k == 0) {
    return 1;
  }
  int ans = exp(n, k / 2);
  ans = (1LL * ans * ans) % MOD;
  if (k & 1) {
    ans = (1LL * ans * n) % MOD;
  }
  return ans;
}

vector< int > build_pot(const auto &n, const auto &k) {
  vector< int > v(n + 5);
  v[1] = k;
  for (int i = 2; i <= n; i += 1) {
    v[i] = (1LL * (exp(i, k + 1) - 1) * exp(i - 1, MOD - 2) - 1 + MOD) % MOD;
    v[i] = (v[i - 1] + v[i]) % MOD;
  }
  return v;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test += 1) {
    int n, k, x0, y0, c, d, ex, ey, f;
    cin >> n >> k >> x0 >> y0 >> c >> d >> ex >> ey >> f;
    auto v = build(n, x0, y0, c, d, ex, ey, f);
    auto pot = build_pot(n, k);
    int ans = 0;
    for (int i = 0; i < n; i += 1) {
      int kappaloiro = (1LL * v[i] * (n - i)) % MOD;
      ans = (1LL * kappaloiro * pot[i + 1] + ans) % MOD;
    }
    cout << "Case #" << test << ": " << ans << "\n";
  }
  return 0;
}