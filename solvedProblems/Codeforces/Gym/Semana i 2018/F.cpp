#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  vector<int> pot;
  pot.push_back(1);
  for (int i = 0; i < 4; ++i)
    pot.push_back(pot.back() * 10);
  while (t-- > 0) {
    string s;
    cin >> s;
    if (int(s.size()) < 2) {
      cout << '1' << '\n';
      continue;
    }
    stringstream ss;
    int len = int(s.size()) - 2;
    ss << s.substr(2, int(s.size()) - 2);
    int num;
    ss >> num;
    cout << (pot[len] / __gcd(pot[len], num)) << '\n';
  }
  return 0;
}