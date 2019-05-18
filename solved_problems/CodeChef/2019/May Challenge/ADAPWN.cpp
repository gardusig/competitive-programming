#include <bits/stdc++.h>
using namespace std;

int n;

vector< vector< int > > build(
  const int &n,
  const vector< vector< char > > &input
) {
  vector< vector< int > > g(n * n);
  const int dx[] = {-1, -1, 1,  1};
  const int dy[] = {-1,  1, 1, -1};
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < n; j += 1) {
      if (input[i][j] != 'O') {
        continue;
      }
      bool flag = false;
      for (int k = 0; k < 4; k += 1) {
        if (k > 1 and flag == false) {
          break;
        }
        int x = i + dx[k];
        int y = j + dy[k];
        if (x < 0 or x >= n or y < 0 or y >= n or input[x][y] != 'O') {
          continue;
        }
        flag = true;
        int kappa = i * n + j;
        int keepo = x * n + y;
        g[kappa].push_back(keepo);
      }
    }
  }
  return g;
}

pair< int, int > get(const int &x) {
  return {x / n, x % n};
}

void solve(const int &n, const vector< vector< int > > &g) {
  vector< int > degree(n * n);
  set< pair< int, int > > s;
  for (int i = 0; i < n * n; i += 1) {
    degree[i] = int(g[i].size());
    if (degree[i] > 0) {
      s.insert({-degree[i], -i});
    }
  }
  vector< int > ans;
  while (int(s.size()) > 0) {
    if (s.begin()->first == 0) {
      break;
    }
    int vertex = -s.begin()->second;
    s.erase(s.begin());
    for (const auto &i: g[vertex]) {
      if (degree[i] == 0) {
        continue;
      }
      s.erase(s.find({-degree[i], -i}));
      degree[i] -= 1;
      s.insert({-degree[i], -i});
    }
    degree[vertex] = 0;
    ans.push_back(vertex);
  }
  cout << ans.size() << endl;
  for (const auto &i: ans) {
    auto kappa = get(i);
    auto keepo = get(g[i][0]);
    cout << kappa.first + 1 << ' ' << kappa.second + 1 << ' ' << (keepo.second > kappa.second ? 'R' : 'L') << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    cin >> n;
    vector< vector< char > > input(n, vector< char >(n));
    for (int i = 0; i < n; i += 1) {
      for (int j = 0; j < n; j += 1) {
        cin >> input[i][j];
      }
    }
    auto g = build(n, input);
    solve(n, g);
  }
  return 0;
}