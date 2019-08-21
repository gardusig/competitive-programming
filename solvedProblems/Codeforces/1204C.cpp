// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

class Solution {
  private:
  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      int N;
      cin >> N;
      int dist[112][112];
      for (int i = 0; i < N; i += 1) {
        for (int j = 0; j < N; j += 1) {
          dist[i][j] = 112345678;
        }
        dist[i][i] = 0;
      }
      for (int i = 0; i < N; i += 1) {
        string s;
        cin >> s;
        for (int j = 0; j < N; j += 1) {
          if (s[j] == '1') {
            dist[i][j] = 1;
          }
        }
      }
      for (int k = 0; k < N; k += 1) {
        for (int i = 0; i < N; i += 1) {
          for (int j = 0; j < N; j += 1) {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
      int Q;
      cin >> Q;
      vector< int > v(Q);
      for (int i = 0; i < Q; i += 1) {
        cin >> v[i];
        v[i] -= 1;
      }
      vector< int > ans;
      for (int i = 0; i < Q; i += 1) {
        if (i == 0 or i == Q - 1 or (dist[ans.back()][v[i + 1]] != dist[ans.back()][v[i]] + dist[v[i]][v[i + 1]])) {
          ans.push_back(v[i]);
        }
      }
      cout << int(ans.size()) << endl;
      for (const int &i: ans) {
        cout << i + 1 << ' ';
      }
      cout << endl;
    }
};

int main() {
  Solution();
  return 0;
}