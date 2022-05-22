#include <bits/stdc++.h>

std::string solve(int N, int D, int C, int M, std::string& S) {
  int dogs = 0;
  for (const char c : S) {
    dogs += (c == 'D');
  }
  if (dogs == 0) {
    return "YES";
  }
  if (dogs > D) {
    return "NO";
  }
  for (const char c : S) {
    if (c == 'C') {
      if (C == 0) {
        return "NO";
      }
      C -= 1;
    } else {
      dogs -= 1;
      if (dogs == 0) {
        return "YES";
      }
      C = std::min(int(S.size()), C + M);
    }
  }
  return "NO";
}

void solve_test_case(const int test_case) {
  int N, D, C, M;
  std::string S;
  std::cin >> N >> D >> C >> M >> S;

  std::string ans = solve(N, D, C, M, S);
  std::cout << "Case #" << test_case << ": " << ans << '\n';
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