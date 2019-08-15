//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

const int MAX_SIZE = 1123456;

class Solution {
  private:
    int T;
    int N;
    vector< int > v;

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
        for (int &i: v) {
          cin >> i;
        }
        int current = 0;
        vector< int > dp[MAX_SIZE];
        dp[0].push_back(0);
        for (int i = 0; i < N; i += 1) {
          current ^= v[i];
          dp[current].push_back(i + 1);
        }
        long long int ans = 0;
        for (int i = 0; i < MAX_SIZE; i += 1) {
          long long int sum = 0;
          for (int j = 0; j < int(dp[i].size()); j += 1) {
            ans += (1LL * j * (dp[i][j] - 1)) - sum;
            sum += dp[i][j];
          }
        }
        cout << ans << endl;
      }
    }
};

int main() {
  Solution().main();
  return 0;
}