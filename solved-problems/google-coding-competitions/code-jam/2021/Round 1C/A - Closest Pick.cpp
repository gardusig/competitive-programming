#include <bits/stdc++.h>

double solve(const int K, std::vector<int> tickets) {
  std::sort(tickets.begin(), tickets.end());
  std::priority_queue<int> pq;
  pq.push(tickets[0] - 1);
  pq.push(K - tickets.back());
  double ans = 0;
  for (int i = 1; i < tickets.size(); i += 1) {
    const int dist = (tickets[i] - tickets[i - 1] - 1);
    pq.push((dist + 1) >> 1);
    ans = std::max(ans, double(dist) / K);
  }
  double best = 0;
  for (int i = 0; i < 2; i += 1) {
    const double value = std::max(0, pq.top());
    pq.pop();
    best += value / K;
  }
  return std::max(ans, best);
}

void solve_test_case(const int test) {
  int N, K;
  std::cin >> N >> K;
  std::vector<int> tickets;
  for (int i = 0; i < N; i += 1) {
    int value;
    std::cin >> value;
    tickets.push_back(value);
  }
  std::cout << "Case #" << test << ": " << std::fixed << std::setprecision(10)
            << solve(K, tickets) << '\n';
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