#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  string s;
  cin >> n >> s;
  int ans = INT_MAX;
  const string goal = "ACTG";
  for (int i = 0; i <= n - 4; i += 1) {
    int current = 0;
    for (int j = 0; j < 4; j += 1) {
      char a = s[i + j];
      char b = goal[j];
      if (a > b) {
        swap(a, b);
      }
      current += min(b - a, a - 'A' + 'Z' - b + 1);
    }
    ans = min(ans, current);
  }
  cout << ans << endl;
  return 0;
}