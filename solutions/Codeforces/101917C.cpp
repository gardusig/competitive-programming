#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, s;
  scanf("%d %d", &n, &s);
  s %= 26;
  s = (s > 0) ? (26 - s) : s;
  string t;
  getline(cin, t);
  while (n-- > 0) {
    getline(cin, t);
    for (const auto &i : t) {
      char ans = i;
      if (isalpha(i)) {
        int kappa = (s + tolower(i) - 'a') % 26;
        ans = kappa + (islower(i) ? 'a' : 'A');
      }
      printf("%c", ans);
    }
    puts("");
  }
  return 0;
}