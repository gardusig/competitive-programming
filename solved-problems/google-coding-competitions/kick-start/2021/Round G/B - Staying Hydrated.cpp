#include <bits/stdc++.h>

std::vector<int> get_close(const int x) {
  const int OFFSET = 112345;
  std::vector<int> ans;
  for (int i = x - OFFSET; i <= x + OFFSET; i += 1) {
    ans.push_back(i);
  }
  return ans;
}

std::vector<int> get_possible_idxs(const std::vector<std::pair<int, int>>& v) {
  std::set<int> possible_idxs;
  int start = INT_MIN;
  int finish = INT_MAX;
  for (const auto& i : v) {
    start = std::max(start, i.first);
    finish = std::min(finish, i.second);
    possible_idxs.insert(i.first);
    possible_idxs.insert(i.second);
  }
  const int middle = (finish + start) >> 1;
  for (const int i : get_close(middle)) {
    possible_idxs.insert(i);
  }
  std::vector<int> ans;
  for (const int i : possible_idxs) {
    ans.push_back(i);
  }
  return ans;
}

std::vector<int64_t> get_l(std::vector<int> possible_idxs,
                           std::vector<std::pair<int, int>> segments) {
  std::vector<int> v;
  for (const auto& segment : segments) {
    v.push_back(segment.second);
  }
  std::sort(v.begin(), v.end());
  std::vector<int64_t> ans;
  int64_t total = 0;
  int segment_idx = 0;
  int previous = possible_idxs.front();
  for (const int i : possible_idxs) {
    total += 1LL * (i - previous) * segment_idx;
    while (segment_idx < v.size() and i >= v[segment_idx]) {
      total += (i - v[segment_idx]);
      segment_idx += 1;
    }
    ans.push_back(total);
    previous = i;
  }
  return ans;
}

std::vector<int64_t> get_r(std::vector<int> possible_idxs,
                           std::vector<std::pair<int, int>> segments) {
  std::vector<int> v;
  for (const auto& segment : segments) {
    v.push_back(segment.first);
  }
  std::sort(v.rbegin(), v.rend());
  std::reverse(possible_idxs.begin(), possible_idxs.end());
  int64_t total = 0;
  int segment_idx = 0;
  int previous = possible_idxs.front();
  std::vector<int64_t> ans;
  for (const int i : possible_idxs) {
    total += 1LL * (previous - i) * segment_idx;
    while (segment_idx < v.size() and i <= v[segment_idx]) {
      total += (v[segment_idx] - i);
      segment_idx += 1;
    }
    ans.push_back(total);
    previous = i;
  }
  std::reverse(ans.begin(), ans.end());
  return ans;
}

int solve(const std::vector<std::pair<int, int>>& v) {
  const auto possible_idxs = get_possible_idxs(v);
  const auto L = get_l(possible_idxs, v);
  const auto R = get_r(possible_idxs, v);
  int ans = -1;
  int64_t best = LLONG_MAX;
  for (int i = 0; i < possible_idxs.size(); i += 1) {
    if (L[i] + R[i] < best) {
      ans = possible_idxs[i];
      best = L[i] + R[i];
    }
  }
  return ans;
}

void solve_test_case(const int test_case) {
  int K;
  std::cin >> K;
  std::vector<std::pair<int, int>> segments[2];
  for (int i = 0; i < K; i += 1) {
    int x1, x2, y1, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    segments[0].push_back({x1, x2});
    segments[1].push_back({y1, y2});
  }
  const int x = solve(segments[0]);
  const int y = solve(segments[1]);
  std::cout << "Case #" << test_case << ": " << x << ' ' << y << '\n';
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