//~ <template>
 
#include <bits/stdc++.h>
using namespace std;
 
mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));
 
//~ </template>
 
class Solution {
private:
  int dp[51][51];
  const int inf = 1123456;
 
public:
  Solution() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
  }
 
  void main() {
    int t;
    cin >> t;
    for (int test = 1; test <= t; test += 1) {
      int n, m;
      cin >> n >> m;
      for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
          dp[i][j] = inf;
        }
      }
      vector< pair< pair< int, int >, int > > queries;
      while (m-- > 0) {
        int x, y, z;
        cin >> x >> y >> z;
        x -= 1;
        y -= 1;
        queries.push_back({{x, y}, z});
        dp[x][y] = z;
        dp[y][x] = z;
      }
      for (int k = 0; k < n; k += 1) {
        for (int i = 0; i < n; i += 1) {
          for (int j = 0; j < n; j += 1) {
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
          }
        }
      }
      bool valid = true;
      for (const auto &query: queries) {
        int x = query.first.first;
        int y = query.first.second;
        int z = query.second;
        valid &= (dp[x][y] == z);
      }
      cout << "Case #" << test << ": ";
      if (valid == false) {
        cout << "Impossible" << endl;
      } else {
        cout << queries.size() << endl;
        for (const auto &query: queries) {
          int x = query.first.first;
          int y = query.first.second;
          int z = query.second;
          cout << x + 1 << ' ' << y + 1 << ' ' << z << endl;
        }
      }
    }
  }
};
 
int main() {
  Solution().main();
  return 0;
}