// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

class Solution {
  private:
    int N;
    int M;
    vector< pair< int, pair< int, int > > > edges;
    vector< pair< int, int > > queries;

    int get(const int& x, vector< int >& parent) {
      if (x != parent[x]) {
        parent[x] = get(parent[x], parent);
      }
      return parent[x];
    }

    void join(const int& x, const int& y, vector< int >& parent, vector< int >& size) {
      size[x] += size[y];
      parent[y] = parent[x];
    }

    vector< long long int > solve() {
      vector< int > parent(N);
      vector< int > size(N, 1);
      for (int i = 0; i < N; i += 1) {
        parent[i] = i;
      }
      int i = 0;
      long long int current = 0;
      vector< long long int > ans(M);
      sort(edges.begin(), edges.end());
      sort(queries.begin(), queries.end());
      for (const pair< int, int >& query : queries) {
        while (i < int(edges.size()) and edges[i].first <= query.first) {
          const int x = get(edges[i].second.first, parent);
          const int y = get(edges[i].second.second, parent);
          if (x == y) {
            continue;
          }
          current += 1LL * size[x] * size[y];
          join(x, y, parent, size);
          i += 1;
        }
        ans[query.second] = current;
      }
      return ans;
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      cin >> N >> M;
      for (int i = 1; i < N; i += 1) {
        int x, y, w;
        cin >> x >> y >> w;
        x -= 1;
        y -= 1;
        edges.push_back({w, {x, y}});
      }
      for (int i = 0; i < M; i += 1) {
        int q;
        cin >> q;
        queries.push_back({q, i});
      }
      for (const long long int& i : solve()) {
        cout << i << ' ';
      }
      cout << endl;
    }
};

int main() {
  Solution();
  return 0;
}