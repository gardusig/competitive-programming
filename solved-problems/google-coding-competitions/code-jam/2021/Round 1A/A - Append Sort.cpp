#include <bits/stdc++.h>

std::string get_added_string(std::string s) {
  int carry = 1;
  for (int i = s.size() - 1; i >= 0; i -= 1) {
    carry += s[i] - '0';
    s[i] = (carry % 10) + '0';
    carry /= 10;
  }
  for (; carry > 0; carry /= 10) {
    s = std::to_string(carry % 10) + s;
  }
  return s;
}

std::string get_next(const std::string& last, const std::string& current) {
  if (current.size() > last.size()) {
    return current;
  }
  if (current.size() == last.size() and current > last) {
    return current;
  }
  const std::string goal = get_added_string(last);
  if (current == goal.substr(0, current.size())) {
    return goal;
  }
  const int add = last.size() - current.size();
  std::string ans = current + std::string(add, '0');
  if (ans <= last) {
    ans.push_back('0');
  }
  return ans;
}

void solve_test_case(const int test) {
  int N;
  std::cin >> N;
  std::string last;
  int ans = 0;
  for (int i = 0; i < N; i += 1) {
    std::string current;
    std::cin >> current;
    const std::string nxt = get_next(last, current);
    ans += nxt.size() - current.size();
    last = nxt;
  }
  std::cout << "Case #" << test << ": " << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}