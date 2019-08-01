#include <bits/stdc++.h>
 
using namespace std;
 
#define N 1010
 
int n, p[N], cnt[N];
 
 
int main(){

  cin >> n;
  int a, b;
  for(int i=1; i<n; i++){
    cin >> a >> b;
    if(b!=n) return !printf("NO\n");
    cnt[a]++;
    p[i]=n;
  }

  for(int i=1; i<n; i++){
    if(!cnt[i]){
      int flag = 0;
      for(int j=i; j<n; j++){
        if(cnt[j]>1){
          cnt[j]--;
          p[i] = p[j];
          p[j] = i;
          flag=1;
          break;
        }
      }
      if(!flag) return !printf("NO\n");
    }
  }

  printf("YES\n");
  for(int i=1; i<n; i++){
    printf("%d %d\n", p[i], i);
  }

}