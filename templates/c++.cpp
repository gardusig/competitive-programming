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
      long long int lowest = 0;
      for (int i = 1; i < L; i += 1) {
        lowest += (1 << i);
      }
      cout << lowest << endl;
    }
};

int main() {
  Solution();
  return 0;
}