#include <bits/stdc++.h>

const int LIMIT = 16;

int get_integer_from_binary_str(const std::string& s) {
  int ans = 0;
  for (int i = 0; i < s.size(); i += 1) {
    if (s[i] == '0') {
      continue;
    }
    ans += (1 << (s.size() - i - 1));
  }
  return ans;
}

int get_flipped(const int N) {
  if (N == 0) {
    return 1;
  }
  int ans = 0;
  for (int i = 0; (1LL << i) <= N; i += 1) {
    if (not(N & (1LL << i))) {
      ans |= (1LL << i);
    }
  }
  return ans;
}

std::string solve(const int S, const int E) {
  std::queue<int> q;
  std::map<int, int> dist;
  dist[S] = 0;
  q.push(S);
  while (not q.empty()) {
    const int i = q.front();
    q.pop();
    if (i == E) {
      return std::to_string(dist[i]);
    }
    if (i < 0 or i >= (1 << LIMIT)) {
      continue;
    }
    const int nxt_dist = dist[i] + 1;
    const int nxt_doubled = i << 1;
    if (not dist.count(nxt_doubled) or nxt_dist < dist[nxt_doubled]) {
      q.push(nxt_doubled);
      dist[nxt_doubled] = nxt_dist;
    }
    const int nxt_flipped = get_flipped(i);
    if (not dist.count(nxt_flipped) or nxt_dist < dist[nxt_flipped]) {
      q.push(nxt_flipped);
      dist[nxt_flipped] = nxt_dist;
    }
  }
  return "IMPOSSIBLE";
}

void solve_test_case(const int test) {
  std::string s, e;
  std::cin >> s >> e;
  assert(s.size() + e.size() <= LIMIT);
  std::cout << "Case #" << test << ": "
            << solve(get_integer_from_binary_str(s),
                     get_integer_from_binary_str(e))
            << '\n';
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