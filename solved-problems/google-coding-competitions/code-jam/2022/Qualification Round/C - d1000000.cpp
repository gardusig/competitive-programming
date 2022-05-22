#include <algorithm>
#include <iostream>
#include <vector>

void solve_test_case(const int test) {
  int N;
  std::cin >> N;
  std::vector<int> v(N);
  for (int& i : v) {
    std::cin >> i;
  }
  std::sort(v.begin(), v.end());
  int current = 1;
  for (const int i : v) {
    if (i >= current) {
      current += 1;
    }
  }
  std::cout << current - 1 << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    std::cout << "Case #" << test << ": ";
    solve_test_case(test);
  }
  return 0;
}