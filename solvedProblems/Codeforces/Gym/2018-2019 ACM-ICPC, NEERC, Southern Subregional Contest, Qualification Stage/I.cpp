#include <bits/stdc++.h>
 
using namespace std;
 
#define N 1010
 
int n, v[N];
 
int main(){

  cin >> n;
  for(int i=0; i<n; i++) cin >> v[i];
  sort(v, v+n);

  long long int ans=0;
  for(int i=1; i<n; i++){
    ans+=v[i]-v[i-1]-1;
  }

  printf("%lld\n", ans);

}