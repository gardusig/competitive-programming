//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

class Solution {
  private:
    vector< int > v;
    vector< int > sum;
    vector< vector< int > > dp;
  
    int solve(const int &i, const int &j) {
      if (dp[i][j] != -1) {
        return dp[i][j];
      }
      if (i == j) {
        dp[i][j] = 0;
        return dp[i][j];
      }
      int ans = INT_MAX;
      for (int k = i; k < j; k += 1) {
        int kappa = (sum[k] - (i > 0 ? sum[i - 1] : 0)) % 100;
        int keepo = (sum[j] - sum[k]) % 100;
        ans = min(ans, kappa * keepo + solve(i, k) + solve(k + 1, j));
      }
      dp[i][j] = ans;
      return dp[i][j];
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }

    void main() {
      int n;
      while (cin >> n) {
        v.resize(n);
        sum.resize(n);
        for (int i = 0; i < n; i += 1) {
          cin >> v[i];
          sum[i] = v[i];
          if (i > 0) {
            sum[i] += sum[i - 1];
          }
        }
        dp.resize(n);
        for (int i = 0; i < n; i += 1) {
          dp[i].resize(n);
          for (int j = 0; j < n; j += 1) {
            dp[i][j] = -1;
          }
        }
        cout << solve(0, n - 1) << endl;
      }
    }
};

int main() {
  Solution().main();
  return 0;
}