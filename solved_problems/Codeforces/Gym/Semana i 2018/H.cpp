#include <iostream>
using namespace std;

int main() {
  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    int n, k; scanf("%d %d", &n, &k);
    k -= (n * (n + 1)) >> 1;
    if (k < 0 or k % n)
      printf("%s\n", "Too drunk to count");
    else
      printf("%d\n", n + 1 + (k / n));
  }
  return 0;
}