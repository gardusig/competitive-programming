//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

class Solution {
  private:
    int T;
    int N;
    bool K_is_one;
    bool C_is_zero;
    vector< double > K;
    vector< double > C;
    vector< double > X;

    double get_ans() {
      double ans = 0;
      for (int i = 0; i < N; i += 1) {
        ans += sqrt(X[i] + C[i]);
      }
      return ans;
    }

    bool solve_1() {
      if (-C[0] > ((C[1] * K[1]) / K[0])) {
        return false;
      }
      if (-C[1] > ((C[0] * K[0]) / K[1])) {
        return false;
      }
      double lo = -C[0];
      double hi = ((C[1] * K[1]) / K[0]);
      for (int iterations = 0; iterations < 123; iterations += 1) {
        const double mid = (hi - lo) / 3.0;
        const double mid1 = lo + mid;
        const double mid2 = hi - mid;
        X[0] = mid1;
        X[1] = -((X[0] * K[0]) / K[1]);
        const double kappa = get_ans();
        X[0] = mid2;
        X[1] = -((X[0] * K[0]) / K[1]);
        const double keepo = get_ans();
        if (kappa > keepo) {
          hi = mid2;
        } else {
          lo = mid1;
        }
      }
      return true;
    }

    bool solve_2() {
      for (int i = 0; i < N; i += 1) {
        X[i] = 0;
      }
      return true;
    }

    bool solve_3() {
      double sum = 0;
      for (int i = 0; i < N; i += 1) {
        sum += C[i];
      }
      if (sum < 0) {
        return false;
      }
      const double avg = sum / N;
      for (int i = 0; i < N; i += 1) {
        X[i] = -C[i] + avg;
      }
      return true;
    }

    bool solve_4() {
      for (int i = 0; i < N; i += 1) {
        X[i] = 0;
      }
      return true;
    }

    bool solve_5() {
      return false;
    }

    bool solve() {
      if (N == 2) {
        return solve_1();
      }
      if (K_is_one == true and C_is_zero == true) {
        return solve_2();
      }
      if (K_is_one == true) {
        return solve_3();
      }
      if (C_is_zero == true) {
        return solve_4();
      }
      return solve_5();
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      cout << fixed;
      cout.precision(2);
    }

    void main() {
      cin >> T;
      while (T-- > 0) {
        cin >> N;
        K.resize(N);
        K_is_one = true;
        for (int i = 0; i < N; i += 1) {
          cin >> K[i];
          K_is_one &= (K[i] == 1);
        }
        C.resize(N);
        C_is_zero = true;
        for (int i = 0; i < N; i += 1) {
          cin >> C[i];
          C_is_zero &= (C[i] == 0);
        }
        X.resize(N);
        if (solve() == true) {
          cout << get_ans();
          for (int i = 0; i < N; i += 1) {
            cout << ' ' << X[i];
          }
          cout << endl;
        } else {
          cout << "-1" << endl;
        }
      }
    }
};

int main() {
  Solution().main();
  return 0;
}