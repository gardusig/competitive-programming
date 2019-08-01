#include <bits/stdc++.h>
 
using namespace std;
 
#define N 5010
#define inf 101010
 
int n, m, bit[N], dp[N], v[N];
 
void update(int pos){
  for(; pos<N; pos+=pos&(-pos)) bit[pos]++;
}
 
int kth(int k){
  int pos=0;
  for(int lg=13; lg>=0; lg--){
    if(pos+(1<<lg) >= N) continue;
    if(bit[pos+(1<<lg)] < k){
      pos+=(1<<lg);
      k-=bit[pos];
    }
  }
  return pos+1;
}
 
int main(){

  scanf("%d %d", &n, &m);

  for(int i=1; i<=n; i++) scanf("%d", &v[i]);

  dp[0] = 0;
  for(int i=1; i<=n; i++){
    dp[i] = -inf;
    for(int j=i; j>0; j--){
      update(v[j]);
      if(kth(ceil((i-j+1)/2.0)) >= m) dp[i] = max(dp[i], dp[j-1]+1);
    }
    //~ printf("dp[%d] = %d\n", i, dp[i]);
    for(int i=1; i<N; i++) bit[i]=0;
  }
  printf("%d\n", max(dp[n], 0));

}