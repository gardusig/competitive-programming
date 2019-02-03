#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000000 + 7;

int exponentiate(const auto &n, const auto &k) {
  if (k == 0) {
    return 1;
  }
  int ans = exponentiate(n, k / 2);
  ans = (1LL * ans * ans) % MOD;
  if ((k & 1) != 0) {
    ans = (1LL * ans * n) % MOD;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, k, m;
    cin >> n >> k >> m;
    int a = exponentiate(n + k, MOD - 2);
    int b = exponentiate(n, MOD - 2);
    int c = (1LL * (n - 1) * b) % MOD;
    int kappa = (1LL * ((m & 1) ? b : a) * exponentiate(c, m / 2)) % MOD;
    int keepo = (1LL * (exponentiate(c, (m / 2)) - 1) * exponentiate(c - 1, MOD -2)) % MOD;
    int ans = (1LL * b * keepo + kappa) % MOD;
    cout << ans << '\n';
  }
  return 0;
}