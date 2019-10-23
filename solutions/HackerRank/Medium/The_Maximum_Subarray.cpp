// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

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
      cin >> T;
      while (T-- > 0) {
        cin >> N;
        v.resize(N);
        for (int i = 0; i < N; i += 1) {
          cin >> v[i];
        }
        long long int sum = 0;
        long long int current = 0;
        long long int ans = LLONG_MIN;
        for (int i = 0; i < N; i += 1) {
          current += v[i];
          ans = max(ans, current);
          if (current < 0) {
            current = 0;
          }
          if (v[i] > 0) {
            sum += v[i];
          }
        }
        if (*max_element(v.begin(), v.end()) < 0) {
          cout << ans << ' ' << *max_element(v.begin(), v.end()) << endl;
        } else {
          cout << ans << ' ' << sum << endl;
        }
      }
    }
};

int main() {
  Solution();
  return 0;
}
