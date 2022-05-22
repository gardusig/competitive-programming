#include <bits/stdc++.h>

int get_cost(const char last_char, const char current_char,
             const std::map<std::string, int>& cost) {
  std::string s;
  s.push_back(last_char);
  s.push_back(current_char);
  const auto it = cost.find(s);
  if (it == cost.end()) {
    return 0;
  }
  return it->second;
}

int64_t solve(const int pos, const char last_char, const std::string& s,
              const std::map<std::string, int>& cost,
              std::map<int, std::map<char, int64_t>>& dp) {
  if (dp.count(pos) and dp[pos].count(last_char)) {
    return dp[pos][last_char];
  }
  if (pos == int(s.size())) {
    return 0;
  }
  int64_t ans = INT_MAX;
  const std::vector<char> available_characters =
      (s[pos] == '?') ? std::vector<char>{'C', 'J'} : std::vector<char>{s[pos]};
  for (const char current_char : available_characters) {
    const int64_t current_cost = get_cost(last_char, current_char, cost);
    const int64_t nxt_cost = solve(pos + 1, current_char, s, cost, dp);
    ans = std::min(ans, current_cost + nxt_cost);
  }
  return dp[pos][last_char] = ans;
}

void solve_test_case(const int test) {
  int X, Y;
  std::string S;
  std::cin >> X >> Y >> S;
  std::map<int, std::map<char, int64_t>> dp;
  const std::map<std::string, int> cost{{"CJ", X}, {"JC", Y}};
  const auto answer = solve(0, '$', S, cost, dp);
  std::cout << "Case #" << test << ": " << answer << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}