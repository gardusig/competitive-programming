#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 51;
const int MAX_BITS = 61;

vector< vector< long long int > > build_sum(const auto &values) {
  int size = int(values.size());
  vector< vector< long long int > > sum(size, vector< long long int >(size));
  for (int i = 0; i < size; i += 1) {
    sum[i][i] = values[i];
    for (int j = i + 1; j < size; j += 1) {
      sum[i][j] = sum[i][j - 1] + values[j];
    }
  }
  return sum;
}

void dfs(const auto &bit, const auto &vertex, const auto &dist, const auto &v, const auto &forbid, auto &used) {
  used[vertex][dist] = true;
  int x = vertex / MAX_SIZE;
  int y = vertex % MAX_SIZE;
  int size = int(v.size());
  int i = y + 1;
  if (y == size - 1) {
    return;
  }
  for (int j = i; j < size; j += 1) {
    if ((v[i][j] & (1LL << bit)) == 0) {
      continue;
    }
    int new_dist = dist + 1;
    int new_vertex = i * MAX_SIZE + j;
    if (forbid[new_vertex][new_dist] == false and used[new_vertex][new_dist] == false) {
      dfs(bit, new_vertex, new_dist, v, forbid, used);
    }
  }
}

void dfs_other(const auto &bit, const auto &vertex, const auto &dist, const auto &v, auto &forbid, auto &used) {
  used[vertex][dist] = false;
  forbid[vertex][dist] = false;
  int x = vertex / MAX_SIZE;
  int y = vertex % MAX_SIZE;
  int size = int(v.size());
  int j = x - 1;
  if (dist == 1) {
    return;
  }
  for (int i = 0; i <= j; i += 1) {
    int new_dist = dist - 1;
    int new_vertex = i * MAX_SIZE + j;
    if (used[new_vertex][new_dist] == true) {
      dfs_other(bit, new_vertex, new_dist, v, forbid, used);
    }
  }
}

bool valid(const auto &bit, const auto &k, const auto &v, auto &forbid) {
  int size = int(v.size());
  vector< vector< bool > > used(MAX_SIZE * MAX_SIZE, vector< bool >(MAX_SIZE, false));
  for (int i = 0; i < size; i += 1) {
    if ((v[0][i] & (1LL << bit)) == 0) {
      continue;
    }
    if (forbid[i][1] == false) {
      dfs(bit, i, 1, v, forbid, used);
    }
  }
  bool ans = false;
  vector< vector< bool > > new_forbid(MAX_SIZE * MAX_SIZE, vector< bool >(MAX_SIZE, true));
  for (int i = 0; i < size; i += 1) {
    int vertex = i * MAX_SIZE + size - 1;
    if (used[vertex][k] == true) {
      ans = true;
      dfs_other(bit, vertex, k, v, new_forbid, used);
    }
  }
  if (ans == true) {
    forbid = new_forbid;
  }
  return ans;
}

long long int solve(const auto &k, const auto &v) {
  long long int ans = 0;
  vector< vector< bool > > forbid(MAX_SIZE * MAX_SIZE, vector< bool >(MAX_SIZE, false));
  for (int bit = MAX_BITS - 1; bit >= 0; bit -= 1) {
    if (valid(bit, k, v, forbid) == true) {
      ans |= (1LL << bit);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector< long long int > v(n);
  for (int i = 0; i < n; i += 1) {
    cin >> v[i];
  }
  int q;
  cin >> q;
  while (q-- > 0) {
    int k;
    cin >> k;
    vector< long long int > values;
    for (int i = 0; i < n; i += 1) {
      int x;
      cin >> x;
      if (x > 0) {
        values.push_back(1LL * x * v[i]);
      }
    }
    cout << ((k <= int(values.size())) ? solve(k, build_sum(values)) : 0) << endl;
  }
  return 0;
}