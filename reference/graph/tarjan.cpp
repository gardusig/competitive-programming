#include <bits/stdc++.h>
using namespace std;

namespace Tarjan {

const int N = 112345;
const int INF = 1e9;

class Edge {
 public:
  int to, id;
  Edge(int to, int id) : to(to), id(id) {}
};

vector<Edge> g[N];
int current_time, n, m;
int pre[N], low[N];
bool used[N], bridge[N], articulation_point[N];

void dfsTarjan(int i, int p) {
  used[i] = true;
  pre[i] = low[i] = current_time++;
  int children = 0;
  for (const auto &e : g[i]) {
    int j = e.to;
    if (!used[j]) {
      ++children;
      dfsTarjan(j, i);
      low[i] = min(low[i], low[j]);
      if (low[j] > pre[i]) {
        bridge[e.id] = true;
      }
      if (i == p && children > 1) {
        articulation_point[i] = true;
      }
      if (i != p && low[j] >= pre[i]) {
        articulation_point[i] = true;
      }
    } else if (j != p) {
      low[i] = min(low[i], pre[j]);
    }
  }
}

void buildTarjan(int _n, const vector<pair<int, int>> &edges) {
  n = _n;
  m = edges.size();
  current_time = 0;
  fill(used, used + n, false);
  fill(articulation_point, articulation_point + n, false);
  fill(bridge, bridge + m, false);
  for (int i = 0; i < n; ++i) g[i].clear();
  for (int i = 0; i < m; ++i) {
    int x = edges[i].first;
    int y = edges[i].second;
    g[x].emplace_back(y, i);
    g[y].emplace_back(x, i);
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) dfsTarjan(i, i);
  }
}

vector<bool> getBridges() { return vector<bool>(bridge, bridge + m); }

vector<bool> getArticulationPoints() {
  return vector<bool>(articulation_point, articulation_point + n);
}

}  // namespace Tarjan

void testTarjan() {
  vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3},
                                  {3, 4}, {4, 5}, {5, 3}};
  Tarjan::buildTarjan(6, edges);
  vector<bool> bridges = Tarjan::getBridges();
  vector<bool> articulation_points = Tarjan::getArticulationPoints();
  for (int i = 0; i < 7; i += 1) {
    if (i == 3) {
      continue;
    }
    assert(bridges[i] == false);
  }
  assert(bridges[3] == true);
  assert(articulation_points[1] == true);
  assert(articulation_points[3] == true);
  assert(articulation_points[0] == false);
  assert(articulation_points[2] == false);
  assert(articulation_points[4] == false);
  cout << "Tarjan's Algorithm Test Passed\n";
}

int main() {
  testTarjan();
  return 0;
}
