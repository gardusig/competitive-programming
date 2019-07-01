#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  string s;
  cin >> s;
  for (int i = 0; i < n - 1; i += 1) {
    if (s[i] > s[i + 1]) {
      cout << "YES" << endl;
      cout << i + 1 << ' ' << i + 2 << endl;
      return 0;
    }
  }
  cout << "NO" << endl;
  return 0;
}