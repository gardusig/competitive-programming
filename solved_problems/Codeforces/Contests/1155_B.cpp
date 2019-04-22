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
  int have = 0;
  int need = 0;
  int remove = n - 11;
  for (int i = 0; i < n and have <= (remove / 2); i += 1) {
    if (s[i] == '8') {
      have += 1;
    } else {
      need += 1;
    }
  }
  if (need > ((remove + 1) / 2)) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }
  return 0;
}