//~ <template>
 
#include <bits/stdc++.h>
using namespace std;
 
mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));
 
//~ </template>
 
class Solution {
private:
  const int MOD = 1000000007;
  vector< int > pot;
 
public:
  Solution() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    pot.push_back(1);
    for (int i = 1; i < 1123456; i += 1) {
      pot.push_back((1LL * pot[i - 1] * 2) % MOD);
    }
  }
 
  void main() {
    int t;
    cin >> t;
    for (int test = 1; test <= t; test += 1) {
      int n, k;
      cin >> n >> k;
      string s;
      cin >> s;
      int sum = 0;
      int ans = 0;
      for (int i = n - 1; i >= 0; i -= 1) {
        const char &c = s[i];
        if (c == 'A') {
          sum -= 1;
        } else {
          sum += 1;
        }
        sum = max(sum, 0);
        if (sum > k) {
          sum -= 2;
          ans = (0LL + ans + pot[i + 1]) % MOD;
        }
        sum = max(sum, 0);
      }
      cout << "Case #" << test << ": " << ans << endl;
    }
  }
};
 
int main() {
  Solution().main();
  return 0;
}