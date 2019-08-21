//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

class Solution {
  private:
    int T;
    string S;

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }

    void main() {
      cin >> T;
      while (T-- > 0) {
        cin >> S;
        int qtd = 0;
        for (const char &c: S) {
          if (c == '1') {
            qtd += 1;
          }
        }
        cout << ((qtd & 1) ? "WIN" : "LOSE") << endl;
      }
    }
};

int main() {
  Solution().main();
  return 0;
}