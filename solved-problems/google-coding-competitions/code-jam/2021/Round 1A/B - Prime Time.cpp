#include <bits/stdc++.h>

const int MAX_SIZE = 499 * 100 + 10;

int divisor[MAX_SIZE];

void build() {
  for (int i = 0; i < MAX_SIZE; i += 1) {
    divisor[i] = i;
  }
  for (int i = 2; i < MAX_SIZE; i += 1) {
    if (divisor[i] != i) {
      continue;
    }
    for (int j = i + i; j < MAX_SIZE; j += i) {
      if (divisor[j] != j) {
        continue;
      }
      divisor[j] = i;
    }
  }
}

std::map<int, int> factors(const int N) {
  std::map<int, int> f;
  for (int current = N; current > 1; current /= divisor[current]) {
    f[divisor[current]] += 1;
  }
  return f;
}

void solve_test_case(const int test) {
  int M;
  std::cin >> M;
  std::map<int, int> map;
  for (int i = 0; i < M; i += 1) {
    int P, N;
    std::cin >> P >> N;
    map[P] += N;
  }
  int64_t ans = 0;
  for (int goal = 1; goal < MAX_SIZE - 10; goal += 1) {
    bool valid = true;
    std::map<int, int> have = map;
    for (const auto& i : factors(goal)) {
      if (have[i.first] < i.second) {
        valid = false;
        break;
      }
      have[i.first] -= i.second;
    }
    if (!valid) {
      continue;
    }
    int64_t sum = 0;
    for (const auto& j : have) {
      sum += 1LL * j.first * j.second;
    }
    if (sum == goal) {
      ans = goal;
    }
  }
  std::cout << "Case #" << test << ": " << ans << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  build();
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}