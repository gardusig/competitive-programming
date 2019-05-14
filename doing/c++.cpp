#include <bits/stdc++.h>
using namespace std;

int exp(const auto &n, const auto &k, const auto &MOD) {
  if (k == 0) {
    return 1;
  }
  int ans = exp(n, k >> 1, MOD);
  ans = (1LL * ans * ans) % MOD;
  if (k & 1) {
    ans = (1LL * ans * n) % MOD;
  }
  return ans;
}

int comb(const auto &n, const auto &k, const auto &fat, const auto &inv_fat, const auto &MOD) {
  int den = (1LL * inv_fat[k] * inv_fat[n - k]) % MOD;
  return (1LL * fat[n] * den) % MOD;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  const int N = 112345;
  const int MOD = 1000000007;
  vector< int > fat(N);
  fat[0] = 1;
  for (int i = 1; i < N; i += 1) {
    fat[i] = (1LL * fat[i - 1] * i) % MOD;
  }
  vector< int > inv_fat(N);
  inv_fat[0] = 1;
  for (int i = 1; i < N; i += 1) {
    inv_fat[i] = (1LL * inv_fat[i - 1] * exp(i, MOD - 2, MOD)) % MOD;
  }
  vector< int > pot(N);
  pot[0] = 1;
  for (int i = 1; i < N; i += 1) {
    pot[i] = (pot[i - 1] << 1) % MOD;
  }
  int t;
  cin >> t;
  while (t-- > 0) {
    int n, k;
    cin >> n >> k;
    if (k & 1) {
      cout << 0 << endl;
      continue;
    }
    int ans = 0;
    for (int l = 0; l <= (k >> 1); l += 1) {
      int r = (k >> 1) - l;
      if (l > (n % k) or r > (k - (n % k))) {
        continue;
      }
      int kappa = comb(n % k, l, fat, inv_fat, MOD);
      int keepo = comb(k - (n % k), r, fat, inv_fat, MOD);
      int block = (1LL * kappa * keepo) % MOD;
      int qtd = ((n / k) * (k >> 1)) + ((n % k) - l);
      ans = (1LL * block * exp(2, qtd, MOD) + ans) % MOD;
    }
    cout << ans << endl;
  }
  return 0;
}