#include <bits/stdc++.h>
#define M 10000100
#define N 200100
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define ue printf("what???\n");
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
 
int a[N], b[N], v[N];
 
main()
{
  int n, h, i, resp, lo, hi, mid, ans;
  scanf("%d%d", &n, &h);
  for(i=0; i<n; i++)
  {
    scanf("%d%d", &a[i], &b[i]);
    if(!i) v[i] = 0;
    else v[i] = v[i-1] + a[i] - b[i-1];
  }
  resp = 0;
  for(i=0; i<n; i++)
  {
    lo = i - 1, hi = n - 1;
    while(lo < hi)
    {
      mid = (lo+hi+1)/2;
      if(v[mid] - v[i] < h) lo = mid, ans = mid;
      else hi = mid - 1;
    }
    resp = max(resp, b[ans] - a[i] + h - v[ans] + v[i]);
  }
  printf("%d\n", resp);
}