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
      int N, L, R;
      cin >> N >> L >> R;
      long long int kappa = 0;
      for (int i = 0; i < L; i += 1) {
        kappa += (1 << i);
      }
      long long int keepo = 0;
      for (int i = 0; i < R; i += 1) {
        keepo += (1 << i);
      }
      cout << kappa + (1LL * (N - L)) << ' ' << keepo + ((1LL << (R - 1)) * (N - R)) << endl;
    }
};

int main() {
  Solution();
  return 0;
}