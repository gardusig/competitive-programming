// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

class Solution {
  private:
    int N;
    int K;
    vector< int > v[2];
    vector< int > component;
    vector< vector< int > > g;
    vector< vector< int > > t;

    void dfs1(const int& i, vector< bool >& used, stack< int >& st) {
      used[i] = true;
      for (const int& j : g[i]) {
        if (used[j] == true) {
          continue;
        }
        dfs1(j, used, st);
      }
      st.push(i);
    }

    void dfs2(const int& i, vector< bool >& used, const int& value) {
      used[i] = true;
      component[i] = value;
      for (const int& j : t[i]) {
        if (used[j] == true) {
          continue;
        }
        dfs2(j, used, value);
      }
    }

    int build() {
      stack< int > st;
      vector< bool > used;
      used = vector< bool >(N + 1, false);
      for (int i = 1; i <= N; i += 1) {
        if (used[i] == false) {
          dfs1(i, used, st);
        }
      }
      int ans = 0;
      component.resize(N + 1);
      used = vector< bool >(N + 1, false);
      while (st.empty() == false) {
        const int i = st.top();
        st.pop();
        if (used[i] == true) {
          continue;
        }
        ans += 1;
        dfs2(i, used, ans);
      }
      return ans;
    }

    vector< char > solve() {
      char current = 'a' - 1;
      vector< char > ans(N);
      vector< char > value(N + 1, '$');
      for (const int& i : v[0]) {
        if (value[component[i]] == '$') {
          if (current - ('a' - 1) < K) {
            current += 1;
          }
          value[component[i]] = current;
        }
        ans[i - 1] = value[component[i]];
      }
      return ans;
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      cin >> N >> K;
      g.resize(N + 1);
      t.resize(N + 1);
      for (int i = 0; i < 2; i += 1) {
        v[i].resize(N);
        for (int j = 0; j < N; j += 1) {
          cin >> v[i][j];
          if (j > 0) {
            g[v[i][j - 1]].push_back(v[i][j]);
            t[v[i][j]].push_back(v[i][j - 1]);
          }
        }
      }
      if (build() < K) {
        cout << "NO" << endl;
      } else {
        cout << "YES" << endl;
        for (const char& i : solve()) {
          cout << i;
        }
        cout << endl;
      }
    }
};

int main() {
  Solution();
  return 0;
}