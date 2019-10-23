#include <bits/stdc++.h>
using namespace std;

std::mt19937 rng(int(std::chrono::steady_clock::now().time_since_epoch().count()));

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test += 1) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector< int > sum(n + 5);
    sum[0] = 0;
    for (int i = 0; i < n; i += 1) {
      sum[i + 1] = sum[i] + (s[i] - '0');
    }
    int size = (n + 1) / 2;
    int ans = 0;
    for (int i = size; i <= n; i += 1) {
      ans = max(ans, sum[i] - sum[i - size]);
    }
    cout << "Case #" << test << ": " << ans << '\n';
  }
  return 0;
}