#include <bits/stdc++.h>

void solve_test_case(const int test) {
  int N;
  std::cin >> N;
  std::vector<int> v(N);
  for (int& i : v) {
    std::cin >> i;
  }
  int answer = 0;
  for (int i = 0; i < N - 1; i += 1) {
    int idx = i;
    for (int j = i + 1; j < N; j += 1) {
      if (v[j] < v[idx]) {
        idx = j;
      }
    }
    idx += 1;
    answer += (idx - i);
    std::reverse(v.begin() + i, v.begin() + idx);
  }
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