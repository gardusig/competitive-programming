#include <bits/stdc++.h>
using namespace std;

const int POT = 62;
const int MOD = 1000000007;

int sum(const auto &n) {
  int total = 0;
  long long int qtd = 0;
  long long int current_odd = 1;
  long long int current_even = 2;
  for (int i = 0; i < POT; i += 1) {
    long long int current_pot = (1LL << i);
    long long int take = (qtd + current_pot > n) ? n - qtd : current_pot;
    long long int x = (i & 1) ? current_even : current_odd;
    if (take > 0 and (take & 1) != 0) {
      total = (0LL + total + x) % MOD;
      x += 2;
      take -= 1;
    }
    long long int y = x + ((take - 1) * 2);
    total = (0LL + total + (((x + y) % MOD) * ((take >> 1) % MOD))) % MOD;
    if (i & 1) {
      current_even = y + 2;
    } else {
      current_odd = y + 2;
    }
    qtd += current_pot;
    if (qtd >= n) {
      break;
    }
  }
  return total;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long int l, r;
  cin >> l >> r;
  int ans = (sum(r) - sum(l - 1) + MOD) % MOD;
  cout << ans << endl;
  return 0;
}