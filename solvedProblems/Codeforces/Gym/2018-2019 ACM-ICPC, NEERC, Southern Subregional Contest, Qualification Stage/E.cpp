#include <bits/stdc++.h>
#define M 10000100
#define N 600100
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define ue printf("what???\n");
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
 
int v[N], esq[N], dir[N], pe[N], pd[N];
map<int, pii> mapa;
 
main()
{
  int i, n, q, c, esquerda, direita;
  set<int> s;
  set<int>::iterator it;
  map<int, int> m;
  scanf("%d", &n);
  for(i=1; i<=n; i++)
    scanf("%d", &v[i]);
  for(i=1; i<=n; i++)
  {
    if(!m.count(v[i])) pe[v[i]] = i;
    else esq[i] = m[v[i]];
    m[v[i]] = i;
  }
  m.clear();
  for(i=n; i>=1; i--)
  {
    if(!m.count(v[i])) pd[v[i]] = i;
    else dir[i] = m[v[i]];
    m[v[i]] = i;
  }
  scanf("%d", &q);
  for(i=0; i<q; i++)
  {
    scanf("%d", &c);

    esquerda = pe[c];
    while(1)
    {
      if(esquerda == 0) break;
      it = s.lower_bound(esquerda);
      if(it == s.end()) break;
      if(mapa[*it].ft <= esquerda) esquerda = dir[esquerda];
      else break;
    }
    pe[c] = esquerda;

    direita = pd[c];
    while(1)
    {
      if(direita == 0) break;
      it = s.lower_bound(direita);
      if(it == s.end()) break;
      if(mapa[*it].ft <= direita) direita = esq[direita];
      else break;
    }
    pd[c] = direita;

    if(!esquerda) continue;

    while(1)
    {
      it = s.lower_bound(esquerda);
      if(it == s.end()) break;
      if(mapa[*it].ft <= direita) s.erase(it);
      else break;
    }
    s.insert(direita);
    mapa[direita] = mp(esquerda, c);
  }

  for(auto i: s)
    for(int j = mapa[i].ft; j <= i; j++)
      v[j] = mapa[i].sd;

  for(i=1; i<=n; i++)
    printf("%d%c", v[i], i == n ? '\n' : ' ');
}