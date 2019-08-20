// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

class Solution {
  private:
    string s;
    int dp[112345][2];

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      cin >> s;
      reverse(s.begin(), s.end());
      for (int i = 0; i < int(s.size()); i += 1) {
        if (i > 0) {
          dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
          dp[i][1] = dp[i - 1][1];
        }
        if (s[i] == '0') {
          dp[i][0] += 1;
        } else {
          dp[i][1] += 1;
        }
      }
      for (int i = 0; i < int(s.size()); i += 1) {
        if (s[i] == '1' and dp[i][0] < dp[i][1]) {
          s[i] = '0';
        }
      }
      reverse(s.begin(), s.end());
      cout << s << endl;
    }
};

int main() {
  Solution();
  return 0;
}