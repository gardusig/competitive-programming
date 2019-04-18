#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t-- > 0) {
    string n;
    int d;
    cin >> n >> d;
    int qtd = 0;
    for (int i = 0; i < int(n.size()); i += 1) {
      n[i] -= '0';
    }
    for (int i = 0; i < int(n.size()); i += 1) {
      int idx = i;
      for (int j = i + 1; j < int(n.size()); j += 1) {
        if (n[j] < n[idx]) {
          idx = j;
        }
      }
      if (n[idx] < d) {
        cout << int(n[idx]);
        qtd += 1;
        i = idx;
      } else {
        break;
      }
    }
    for (int i = 0; i < int(n.size()) - qtd; i += 1) {
      cout << d;
    }
    cout << endl;
  }
  return 0;
}