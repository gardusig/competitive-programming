#include <algorithm>
#include <iostream>
#include <vector>

void solve_test_case(const int test) {
  int R, C;
  std::cin >> R >> C;
  R <<= 1;
  C <<= 1;
  for (int i = 0; i < R + 1; i += 1) {
    std::string line;
    for (int j = 0; j < C + 1; j += 1) {
      char c;
      if (i & 1) {
        c = (j & 1) ? '.' : '|';
      } else {
        c = (j & 1) ? '-' : '+';
      }
      line.push_back(c);
    }
    if (i < 2) {
      line[0] = '.';
      line[1] = '.';
    }
    std::cout << line << std::endl;
  }
}

int main() {
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    std::cout << "Case #" << test << ":" << std::endl;
    solve_test_case(test);
  }
  return 0;
}