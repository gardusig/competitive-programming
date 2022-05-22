#include <bits/stdc++.h>
using namespace std;
struct pais
{
  int o, p, b, id;
};

bool ord(pais a, pais b)
{
  if (a.o == b.o)
  {
    if (a.p == b.p)
    {
      if (a.b == b.b)
      {
        return a.id < b.id;
      }
      return a.b > b.b;
    }
    return a.p > b.p;
  }
  return a.o > b.o;
}

int main()
{
  int paises, mod;
  pais a;
  cin >> paises >> mod;
  pais vp[paises];
  for (int i = 0; i < paises; ++i)
  {
    vp[i].id = i;
    vp[i].o = vp[i].p = vp[i].b = 0;
  }
  for (int i = 0; i < mod; i++)
  {
    int v[3];
    for (int j = 0; j < 3; j++)
    {
      cin >> v[j];
      if (j == 0)
      {
        vp[v[j] - 1].o++;
      }
      else if (j == 1)
      {
        vp[v[j] - 1].p++;
      }
      else
      {
        vp[v[j] - 1].b++;
      }
    }
  }
  sort(vp, vp + paises, ord);

  for (int i = 0; i < paises; i++)
  {
    if (i != paises - 1)
    {
      cout << vp[i].id + 1 << ' ';
    }
    else
    {
      cout << vp[i].id + 1 << endl;
    }
  }
}