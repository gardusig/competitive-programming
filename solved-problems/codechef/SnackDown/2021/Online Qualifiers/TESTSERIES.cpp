#include <bits/stdc++.h>

void solve_test_case(const int test_case) {
  const int GAMES = 5;
  std::unordered_map<int, std::string> teams{{1, "INDIA"}, {2, "ENGLAND"}};
  std::unordered_map<int, int> won_games;
  for (int game = 0; game < GAMES; game += 1) {
    int result;
    std::cin >> result;
    if (teams.count(result) == 0) {
      continue;
    }
    won_games[result] += 1;
  }
  if (won_games[1] != won_games[2]) {
    std::cout << (won_games[1] > won_games[2] ? teams[1] : teams[2]) << '\n';
  } else {
    std::cout << "DRAW" << '\n';
  }
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int tests;
  std::cin >> tests;
  for (int test_case = 1; test_case <= tests; test_case += 1) {
    solve_test_case(test_case);
  }
  return 0;
}
