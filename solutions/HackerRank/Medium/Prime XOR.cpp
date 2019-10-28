//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

const int MOD = 1000000000 + 7;
const int MAX_SIZE = 112345;

class Solution {
  private:
    int Q;
    int N;
    int have[MAX_SIZE];
    int dp[1123][6123];
    vector< bool > primes;

    void build_primes() {
      primes = vector< bool >(MAX_SIZE, false);
      for (int i = 2; i < MAX_SIZE; i += 1) {
        primes[i] = true;
        for (int j = 2; 1LL * j * j <= i; j += 1) {
          if ((i % j) == 0) {
            primes[i] = false;
            break;
          }
        }
      }
    }

    int solve(const int &i, const int &j) {
      if (dp[i - 3500][j] != -1) {
        return dp[i - 3500][j];
      }
      if (i > 4500) {
        dp[i - 3500][j] = primes[j];
        return dp[i - 3500][j];
      }
      long long int ans = 0;
      ans += 1LL * (1 + (have[i] >> 1)) * solve(i + 1, j);
      ans += 1LL * ((have[i] + 1) >> 1) * solve(i + 1, j ^ i);
      dp[i - 3500][j] = ans % MOD;
      return dp[i - 3500][j];
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      build_primes();
      cin >> Q;
      while (Q-- > 0) {
        cin >> N;
        for (int i = 3500; i <= 4500; i += 1) {
          have[i] = 0;
        }
        for (int i = 0; i < N; i += 1) {
          int value;
          cin >> value;
          have[value] += 1;
        }
        for (int i = 0; i < 1123; i += 1) {
          for (int j = 0; j < 6123; j += 1) {
            dp[i][j] = -1;
          }
        }
        cout << solve(3500, 0) << endl;
      }
    }
};

int main() {
  Solution();
  return 0;
}
