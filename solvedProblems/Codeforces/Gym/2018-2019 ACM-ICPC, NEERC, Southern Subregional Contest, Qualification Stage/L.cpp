//~ <template>
 
#include <bits/stdc++.h>
using namespace std;
 
mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));
 
//~ </template>
 
class Solution {
  private:
 
  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }
 
    void main() {
      int y;
      int n;
      cin >> n >> y;
      vector< long long int > a(n);
      for (int i = 0; i < n; i += 1) {
        cin >> a[i];
      }
      int m;
      cin >> m >> y;
      vector< long long int > b(m);
      for (int i = 0; i < m; i += 1) {
        cin >> b[i];
      }
      int ans = 2;
      for (int pot = 1; pot < 40; pot += 1) {
        long long int current = 1LL << pot;
        unordered_map< long long int, int > c, d;
        for (const auto &i: a) {
          c[i % current] += 1;
        }
        for (const auto &i: b) {
          d[i % current] += 1;
        }
        for (const auto &i: c) {
          ans = max(ans, i.second + d[(i.first + (current >> 1)) % current]);
        }
        for (const auto &i: d) {
          ans = max(ans, i.second + c[(i.first + (current >> 1)) % current]);
        }
      }
      cout << ans << endl;
    }
};
 
int main() {
  Solution().main();
  return 0;
}