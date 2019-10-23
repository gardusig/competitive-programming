#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-1,  0, 0, 1};
const int dy[] = { 0, -1, 1, 0};

bool valid(const auto &guess, const auto &n, const auto &m, const auto &dist) {
  set< pair< int, int > > available;
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < m; j += 1) {
      available.insert({i, j});
    }
  }
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < m; j += 1) {
      if (dist[i][j] > guess) {
        set< pair< int, int > > new_available;
        for (const auto &k: available) {
          if (abs(k.first - i) + abs(k.second - j) <= guess) {
            new_available.insert(k);
          }
        }
        available = new_available;
      }
    }
  }
  return int(available.size()) > 0;
}

int solve(const auto &n, const auto &m, const auto &v) {
  queue< pair< int, pair< int, int > > > q;
  vector< vector< int > > dist(n, vector< int >(m, INT_MAX));
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < m; j += 1) {
      if (v[i][j] == '1') {
        dist[i][j] = 0;
        q.push({dist[i][j], {i, j}});
      }
    }
  }
  while (q.empty() == false) {
    int current_dist = q.front().first;
    int i = q.front().second.first;
    int j = q.front().second.second;
    q.pop();
    if (current_dist > dist[i][j]) {
      continue;
    }
    for (int k = 0; k < 4; k += 1) {
      int x = i + dx[k];
      int y = j + dy[k];
      if (x < 0 or x >= n or y < 0 or y >= m) {
        continue;
      }
      int nxt_dist = dist[i][j] + 1;
      if (nxt_dist < dist[x][y]) {
        dist[x][y] = nxt_dist;
        q.push({nxt_dist, {x, y}});
      }
    }
  }
  int lo = 0, hi = n * m;
  while (lo <= hi) {
    const auto mid = lo + ((hi - lo) / 2);
    if (valid(mid, n, m, dist) == true) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return hi + 1;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test += 1) {
    int n, m;
    cin >> n >> m;
    vector< string > v(n);
    for (int i = 0; i < n; i += 1) {
      cin >> v[i];
    }
    cout << "Case #" << test << ": " << solve(n, m, v) << endl;
  }
  return 0;
}