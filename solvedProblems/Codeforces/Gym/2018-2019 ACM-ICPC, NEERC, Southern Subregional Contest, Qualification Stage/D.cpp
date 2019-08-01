#include <bits/stdc++.h>
#define N 10000100
#define M 200100
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define ue printf("what???\n");
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
 
 
int last[N];
int query[M], now;
vii v;
map<int, vector<int> > divi;
 
void crivo()
{
  for(int i=2; i<N; i++)
  {
    if(last[i]) continue;
    for(int j=i; j<N; j+=i) last[j] = i;
  }
}
 
void termina()
{
  printf("NO\n");
  exit(0);
}
 
void f(int i, int n)
{
  if(i == v.size())
  {
    divi[now].pb(n);
    return;
  }
  int aux = n;
  for(int j = 0; j <= v[i].sd; j++)
    f(i+1, aux), aux *= v[i].ft;
}
 
main()
{
  int n, i, k, tmp, cnt;
  map<int, int> m, save;
  scanf("%d", &n);
  crivo();
  for(i=0; i<n; i++)
  {
    scanf("%d", &query[i]);
    m[query[i]]++;
  }
  for(auto aux: m)
  {
    if(aux.ft == 1)
    {
      if(aux.sd > 1) termina();
    }
    else
    {
      now = aux.ft;
      tmp = aux.ft;
      v.clear();
      while(tmp > 1)
      {
        k = last[tmp];
        cnt = 0;
        while(tmp % k == 0)
          tmp /= k, cnt++;
        v.pb(mp(k, cnt));
      }
      divi[now].clear();
      f(0, 1);
      if(divi[now].size() < aux.sd) termina();
    }
  }
  printf("YES\n");
  for(i=0; i<n; i++)
  {
    if(query[i] == 1) printf("1 1\n");
    else
    {
      if(!save.count(query[i])) save[query[i]] = 0;
      else save[query[i]]++;
      printf("%d %d\n", divi[query[i]][save[query[i]]], query[i] / divi[query[i]][save[query[i]]]);
    }
  }
}


