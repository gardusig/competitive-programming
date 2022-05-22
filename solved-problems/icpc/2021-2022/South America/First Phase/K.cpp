#include <bits/stdc++.h>

bool solve(int T, int D, int M, std::vector<int>& V) {
  V.push_back(0);
  V.push_back(D);
  std::sort(V.begin(), V.end());
  for (int i = 1; i < V.size(); i += 1) {
    if (V[i] - V[i - 1] >= T) {
      return true;
    }
  }
  return false;
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int T, D, M;
  std::cin >> T >> D >> M;
  std::vector<int> V(M);
  for (int& i : V) {
    std::cin >> i;
  }

  const bool ans = solve(T, D, M, V);
  std::cout << (ans ? 'Y' : 'N') << '\n';

  return 0;
}
