#include <bits/stdc++.h>

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int N, K;
  std::cin >> N >> K;

  std::vector<int> number(N);
  std::vector<int> color(N);

  for (int i = 0; i < N; i += 1) {
    std::cin >> number[i] >> color[i];
  }

  bool valid = true;
  for (int i = 0; i < N; i += 1) {
    if (number[i] == i + 1) {
      continue;
    }
    if (color[i] != color[number[i] - 1]) {
      valid = false;
    }
  }
  std::cout << (valid ? 'Y' : 'N') << '\n';

  return 0;
}