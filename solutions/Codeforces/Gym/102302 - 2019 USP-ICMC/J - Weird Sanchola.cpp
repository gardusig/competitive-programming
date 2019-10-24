// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

class Solution {
  private:
    int N;
    vector< int > V;

    bool prime(const int &n) {
      for (int i = 2; 1LL * i * i <= n; i += 1) {
        if ((n % i) == 0) {
          return false;
        }
      }
      return true;
    }

    long long int check(const int &value) {
      long long int sum = 0;
      for (const int &i: V) {
        sum += abs(value - i);
      }
      return sum;
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      cin >> N;
      V.resize(N);
      for (int i = 0; i < N; i += 1) {
        cin >> V[i];
      }
      double lo = 0;
      double hi = INT_MAX;
      for (int iterations = 0; iterations < 256; iterations += 1) {
        const double mid = (hi - lo) / 3;
        const double mid1 = lo + mid;
        const double mid2 = hi - mid;
        if (check(mid1) < check(mid2)) {
          hi = mid2;
        } else {
          lo = mid1;
        }
      }
      vector< int > possible;
      for (int i = floor(lo), j = 0; i > 1 and j < 3; i -= 1) {
        if (prime(i) == true) {
          possible.push_back(i);
          j += 1;
        }
      }
      for (int i = ceil(lo), j = 0; i < 1123456789 and j < 3; i += 1) {
        if (prime(i) == true) {
          possible.push_back(i);
          j += 1;
        }
      }
      long long int ans = LLONG_MAX;
      for (const int &value: possible) {
        ans = min(ans, check(value));
      }
      cout << ans << endl;
    }
};

int main() {
  Solution();
  return 0;
}