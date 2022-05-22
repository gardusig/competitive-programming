#include <bits/stdc++.h>

const int MAX_SIZE = 112345;

int person_to_h[MAX_SIZE];
int h_to_person[MAX_SIZE];
std::vector<int> g[MAX_SIZE];

void dfs(const int i, const int p, int& idx) {
  person_to_h[i] = idx;
  h_to_person[idx] = i;
  idx += 1;
  for (const int j : g[i]) {
    if (j == p) {
      continue;
    }
    dfs(j, i, idx);
  }
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int N;
  std::cin >> N;

  int population = 0;
  std::vector<int> to_kill;

  for (int i = 0; i < N; i += 1) {
    int type, x;
    std::cin >> type >> x;
    x -= 1;
    if (type == 2) {
      to_kill.push_back(x);
    } else {
      population += 1;
      g[x].push_back(population);
      g[population].push_back(x);
    }
  }

  int h = 0;
  dfs(0, 0, h);

  std::set<int> alive;
  for (int i = 0; i <= population; i += 1) {
    alive.insert(person_to_h[i]);
  }

  for (const int killed : to_kill) {
    alive.erase(person_to_h[killed]);
    std::cout << h_to_person[*alive.begin()] + 1 << '\n';
  }

  return 0;
}
