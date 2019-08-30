#include <bits/stdc++.h>
using namespace std;

const int N = 512;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  int v[N][N];
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j < m; j += 1) {
      cin >> v[i][j];
    }
  }
  int ans[N];
  for (int i = 0; i < n; i += 1) {
    ans[i] = 0;
  }
  int current = 0;
  for (int i = 0; i < n; i += 1) {
    current ^= v[i][0];
  }
  bool solved = false;
  if (current == 0) {
    for (int i = 0; i < n and solved == false; i += 1) {
      for (int j = 1; j < m and solved == false; j += 1) {
        if (v[i][j] != v[i][0]) {
          ans[i] = j;
          solved = true;
        }
      }
    }
  } else {
    solved = true;
  }
  if (solved == false) {
    cout << "NIE" << endl;
  } else {
    cout << "TAK" << endl;
    for (int i = 0; i < n; i += 1) {
      cout << ans[i] + 1 << (i == n - 1 ? '\n' : ' ');
    }
  }
  return 0;
}