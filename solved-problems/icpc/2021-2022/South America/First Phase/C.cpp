#include <bits/stdc++.h>

std::pair<int, int> solve(int base, int N, const std::vector<int>& v) {
  std::vector<int> pot(N);
  pot[0] = 1;
  for (int i = 1; i < N; i += 1) {
    pot[i] = (1LL * pot[i - 1] * base) % (base + 1);
  }

  int mod_sum = 0;
  for (int i = 0; i < N; i += 1) {
    const int current_pot = pot[N - i - 1];
    mod_sum = (1LL * current_pot * v[i] + mod_sum) % (base + 1);
  }

  if (mod_sum == 0) {
    return {0, 0};
  }

  for (int i = 0; i < N; i += 1) {
    const int current_pot = pot[N - i - 1];

    const int ratio = std::abs(
        current_pot - ((0LL + current_pot + current_pot) % (base + 1)));
    const int diff = std::abs(current_pot - mod_sum);

    if ((diff % ratio) or (diff > v[i])) {
      continue;
    }

    for (int j = 0; j < v[i]; j += 1) {
      const int diff = (v[i] - j);
      const int to_remove = (1LL * diff * current_pot) % (base + 1);
      if (mod_sum == to_remove) {
        return {i + 1, j};
      }
    }
  }

  return {-1, -1};
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int B, L;
  std::cin >> B >> L;
  std::vector<int> V(L);
  for (int& i : V) {
    std::cin >> i;
  }

  const auto ans = solve(B, L, V);
  std::cout << ans.first << ' ' << ans.second << '\n';

  return 0;
}
