#include <bits/stdc++.h>

bool valid(const int pos, const int last, const std::string& s) {
  if (pos == s.size()) {
    return last != -1;
  }
  if (last != -1 and s[pos] == '0') {
    return false;
  }
  int current = 0;
  for (int i = pos; i < s.size() - !pos; i += 1) {
    current *= 10;
    current += s[i] - '0';
    if ((last == -1 or current == last + 1)) {
      if (valid(i + 1, current, s)) {
        return true;
      }
    }
    if (last != -1 and current > last + 1) {
      return false;
    }
  }
  return false;
}

void solve_test_case(const int test) {
  int64_t N;
  std::cin >> N;
  assert(N <= 1123456);
  do {
    N += 1;
  } while (not valid(0, -1, std::to_string(N)));
  std::cout << "Case #" << test << ": " << N << '\n';
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