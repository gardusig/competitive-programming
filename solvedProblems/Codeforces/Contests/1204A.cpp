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
      string s;
      cin >> s;
      int ans = 0;
      bool kappaloiro = false;
      int size = int(s.size()) - 1;
      for (const char &i: s) {
        if (i == '1') {
          if (ans == 0) {
            ans = (size >> 1);
            if (size & 1) {
              kappaloiro = true;
            }
          } else {
            kappaloiro = true;
          }
        }
        size -= 1;
      }
      cout << ans + kappaloiro << endl;
    }
};

int main() {
  Solution();
  return 0;
}