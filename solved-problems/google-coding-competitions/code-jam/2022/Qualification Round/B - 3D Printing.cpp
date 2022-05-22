#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

void solve_test_case(const int test) {
  std::vector<int> available(4, INT_MAX);
  for (int i = 0; i < 3; i += 1) {
    for (int j = 0; j < 4; j += 1) {
      int value;
      std::cin >> value;
      available[j] = std::min(available[j], value);
    }
  }
  int64_t sum = 0;
  for (int j = 0; j < 4; j += 1) {
    sum += available[j];
  }
  const int GOAL = 1'000'000;
  if (sum < GOAL) {
    std::cout << " IMPOSSIBLE" << std::endl;
    return;
  }
  int remaining = GOAL;
  for (int j = 0; j < 4; j += 1) {
    std::cout << " " << std::min(available[j], remaining);
    remaining -= available[j];
    remaining = std::max(0, remaining);
  }
  std::cout << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    std::cout << "Case #" << test << ":";
    solve_test_case(test);
  }
  return 0;
}