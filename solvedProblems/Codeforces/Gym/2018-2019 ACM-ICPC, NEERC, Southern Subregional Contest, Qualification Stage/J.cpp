#include <bits/stdc++.h>
 
using namespace std;
 
#define N 1010
 
typedef long long ll;
 
ll gcd(ll a, ll b){
  if(a%b == 0) return b;
  return gcd(b, a%b);
}
 
ll a, b, x, y;
 
int main(){

  cin >> a >> b >> x >> y;

  ll d = gcd(x, y);
  x/=d;
  y/=d;

  printf("%lld\n", min(a/x, b/y));

}