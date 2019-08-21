//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

class Solution {
  private:
    int T;
    int N;
    vector< int > v;
    vector< long long int > sum;
    vector< vector< long long int > > dp;
    
    long long int solve(const int &i, const int &j) {
      if (dp[i][j] != -1) {
        return dp[i][j];
      }
      if (i == j) {
        dp[i][j] = 0;
        return dp[i][j];
      }
      long long int ans = LLONG_MAX;
      for (int k = i; k < j; k += 1) {
        ans = min(ans, solve(i, k) + solve(k + 1, j));
      }
      dp[i][j] = ans + sum[j] - (i > 0 ? sum[i - 1] : 0);
      return dp[i][j];
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }

    void main() {
      cin >> T;
      while (T-- > 0) {
        cin >> N;
        v.resize(N);
        for (int i = 0; i < N; i += 1) {
          cin >> v[i];
          v.push_back(v[i]);
        }
        sum.resize(N + N);
        sum[0] = v[0];
        for (int i = 1; i < N + N; i += 1) {
          sum[i] = sum[i - 1] + v[i];
        }
        dp.resize(N + N + 5);
        for (int i = 0; i < N + N + 5; i += 1) {
          dp[i].resize(N + N + 5);
          for (int j = 0; j < N + N + 5; j += 1) {
            dp[i][j] = -1;
          }
        }
        long long int ans = LLONG_MAX;
        for (int i = 0; i < N; i += 1) {
          ans = min(ans, solve(i, i + N - 1));
        }
        cout << ans << endl;
      }
    }
};

int main() {
  Solution().main();
  return 0;
}