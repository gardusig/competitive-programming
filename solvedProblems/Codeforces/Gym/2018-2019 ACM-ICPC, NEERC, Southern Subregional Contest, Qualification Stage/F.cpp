#include <bits/stdc++.h>
using namespace std;
 
const int MAX_SIZE = 1000000;
 
int v[MAX_SIZE][30];
 
int check(const string &s) {
  int kappa = s[0] + s[1] + s[2];
  int keepo = s[3] + s[4] + s[5];
  return abs(kappa - keepo);
}
 
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(v, 0, sizeof v);
  for (int i = 0; i < MAX_SIZE; i += 1) {
    string s = to_string(i);
    int qtd = 6 - int(s.size());
    for (int i = 0; i < qtd; i += 1) {
      s = "0" + s;
    }
    const int &value = check(s);
    v[i][value] = 1;
    if (i > 0) {
      for (int j = 0; j < 30; j += 1) {
        v[i][j] += v[i - 1][j];
      }
    }
  }
  int n;
  cin >> n;
  while (n-- > 0) {
    string s;
    cin >> s;
    stringstream ss;
    ss << s;
    int x;
    ss >> x;
    if (x == 0) {
      cout << 0 << endl;
      continue;
    }
    int ans = 0;
    const int value = check(s);
    for (int i = 0; i < value; i += 1) {
      ans += v[x - 1][i];
    }
    cout << ans << endl;
  }
  return 0;
}