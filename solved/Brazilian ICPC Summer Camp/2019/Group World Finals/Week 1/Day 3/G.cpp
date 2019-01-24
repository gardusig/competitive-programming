#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  string s;
  cin >> s;
  int ans = 0;
  int side = 0;
  for (const auto &i: s) {
    if (i == 'L') {
      side -= 1;
    } else {
      side += 1;
    }
    if (side % 4 == 0) {
      if (side == 4) {
        ans += 1;
      }
      side = 0;
    }
  }
  cout << ans << '\n';
  return 0;
}
