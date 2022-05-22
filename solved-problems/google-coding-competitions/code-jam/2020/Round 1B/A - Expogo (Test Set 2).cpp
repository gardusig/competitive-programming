#include <bits/stdc++.h>

const int JUMP_LIMIT = 8;
const std::vector<int> dx{0, 0, 1, -1};
const std::vector<int> dy{1, -1, 0, 0};

std::map<std::pair<int, std::pair<int, int>>, std::pair<int, int>> parent;

std::vector<std::pair<int, std::pair<int, int>>> get_edges(const int X,
                                                           const int Y,
                                                           const int jump) {
  if (jump > JUMP_LIMIT) {
    return {};
  }
  std::vector<std::pair<int, std::pair<int, int>>> edges;
  for (int i = 0; i < 4; i += 1) {
    const int64_t x = (1LL << jump) * dx[i] + X;
    const int64_t y = (1LL << jump) * dy[i] + Y;
    edges.push_back({jump + 1, {x, y}});
  }
  return edges;
}

void bfs() {
  std::queue<std::pair<int, std::pair<int, int>>> q;
  const std::pair<int, std::pair<int, int>> starting_point{0, {0, 0}};
  q.push(starting_point);
  parent[starting_point] = {0, 0};
  while (not q.empty()) {
    const int current_jump = q.front().first;
    const int x = q.front().second.first;
    const int y = q.front().second.second;
    q.pop();
    for (const auto& edge : get_edges(x, y, current_jump)) {
      if (parent.count(edge)) {
        continue;
      }
      q.push(edge);
      parent[edge] = {x, y};
    }
  }
}

char get_path_command(const int previous_x, const int previous_y, const int x,
                      const int y) {
  if (x != previous_x) {
    return previous_x < x ? 'E' : 'W';
  }
  return previous_y < y ? 'N' : 'S';
}

std::string backtrace(const int final_cost, int x, int y) {
  std::string ans;
  for (int cost = final_cost; cost > 0; cost -= 1) {
    const std::pair<int, int>& p = parent[{cost, {x, y}}];
    const int previous_x = p.first;
    const int previous_y = p.second;
    ans.push_back(get_path_command(previous_x, previous_y, x, y));
    x = previous_x;
    y = previous_y;
  }
  assert(x == 0);
  assert(y == 0);
  std::reverse(ans.begin(), ans.end());
  return ans;
}

std::string solve(const int X, const int Y) {
  for (int cost = 0; cost <= JUMP_LIMIT; cost += 1) {
    if (parent.count({cost, {X, Y}})) {
      return backtrace(cost, X, Y);
    }
  }
  return "IMPOSSIBLE";
}

void solve_test_case(const int test) {
  int X, Y;
  std::cin >> X >> Y;
  const std::string answer = solve(X, Y);
  std::cout << "Case #" << test << ": " << answer << std::endl;
}

int main() {
  bfs();
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}