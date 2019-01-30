#include <bits/stdc++.h>
using namespace std;

string get(const auto &a, const auto &b) {
  if (int(a.size()) == int(b.size())) {
    return max(a, b);
  }
  return (int(a.size()) > int(b.size())) ? a : b;
}

vector< string > build(const auto &other) {
  vector< string > ans;
  vector< int > v = other;
  for (int a = 1; a < 10; a += 1) {
    if (v[a] > 0) {
      v[a] -= 1;
      for (int b = 0; b < 10; b += 1) {
        if (v[b] > 0) {
          v[b] -= 1;
          for (int c = 0; c < 10; c += 1) {
            if (v[c] > 0) {
              v[c] -= 1;
              if ((a + b + c) % 3 == 0) {
                ans.push_back(string(1, '0' + a) + string(1, '0' + b) + string(1, '0' + c));
              }
              v[c] += 1;
            }
          }
          v[b] += 1;
        }
      }
      v[a] += 1;
    }
  }
  return ans;
}

string solve(const auto &other, const auto &s) {
  string ans = s;
  vector< int > v = other;
  for (int i = 0; i < int(s.size()); i += 1) {
    v[s[i] - '0'] -= 1;
  }
  int x = s[int(s.size()) - 2] - '0';
  int y = s[int(s.size()) - 1] - '0';
  bool flag = true;
  while (flag == true) {
    flag = false;
    for (int z = 9; z >= 0; z -= 1) {
      if ((x + y + z) % 3 == 0 and v[z] > 0) {
        ans += string(1, '0' + z);
        flag = true;
        v[z] -= 1;
        x = y;
        y = z;
        break;
      }
    }
  }
  return ans;
}

string solve_other(const auto &other) {
  vector< int > v = other;
  string ans = "";
  for (int i = 9; i >= 0; i -= 1) {
    while (int(ans.size()) < 2 and v[i] > 0) {
      v[i] -= 1;
      ans += string(1, '0' + i);
    }
  }
  if (ans == "00") {
    ans = "0";
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  vector< int > v(10);
  for (int i = 0; i < 10; i += 1)
    cin >> v[i];
  string ans = "";
  for (const auto &i: build(v)) {
    ans = get(ans, solve(v, i));
  }
  ans = get(ans, solve_other(v));
  cout << ans << '\n';
  return 0;
}
