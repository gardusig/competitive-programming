#include <bits/stdc++.h>
 
using namespace std;
 
#define N 401010
 
typedef long long ll;
 
struct event{
  int x, id;
  bool ini;
};
 
int n, m, d, ans[N], answer;
vector<event> vet;
 
bool comp(event a, event b){
  if(a.x != b.x) return a.x < b.x;
  if(a.ini != b.ini) return a.ini;
  return a.id < b.id;
}
 
void solve(){
  sort(vet.begin(), vet.end(), comp);
  set<int> s;
  int cont=0, answer=0;
  for(event e : vet){
    if(e.ini){
      if(answer == cont){
        ans[e.id] = ++cont;
        answer = cont;
      }else{
        ans[e.id] = *s.begin();
        s.erase(s.begin());
        cont++;
      }
    }else{
      cont--;
      s.insert(ans[e.id]);
    }
  }
  printf("%d\n", answer);
  for(int i=1; i<=n; i++) printf("%d ", ans[i]);
  printf("\n");
}
 
int main(){

  scanf("%d %d %d", &n, &m, &d);

  int a, b;
  for(int i=1; i<=n; i++) {
    scanf("%d", &a);
    vet.push_back({a, i, true});
    vet.push_back({a+d, i, false});
  }
  solve();
}