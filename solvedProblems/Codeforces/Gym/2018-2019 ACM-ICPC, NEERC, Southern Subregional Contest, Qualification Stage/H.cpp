#include <bits/stdc++.h>
using namespace std;
 
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  int maxH, minH, maxW, minW;
  cin >> n >> m >> minH >> minW >> maxH >> maxW;
  int ans = 0;
  ans += (minH - 1) * (m & 1);
  ans += (n - maxH) * (m & 1);
  ans += (maxH - minH + 1) * (((minW - 1) & 1) + ((m - maxW) & 1));
  cout << (ans >> 1) + (ans & 1) << endl;
  return 0;
}