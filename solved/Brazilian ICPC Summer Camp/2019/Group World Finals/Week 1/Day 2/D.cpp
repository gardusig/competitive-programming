#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  priority_queue< pair< int, int > > pq;
  for (int i = 0; i < n; i += 1) {
    int x; 
    cin >> x;
    pq.push({x, i});
  }
  queue< pair< int, int > > q;
  while (pq.empty() == false) {
    q.push(pq.top());
    pq.pop();
    while (q.empty() == false) {
      auto current = q.front();
      q.pop();
      while (current.first > 0) {
        auto nxt = pq.top();
        pq.pop();
        current.first -= 1;
        nxt.first -= 1;
        cout << current.second + 1 << ' ' << nxt.second + 1 << '\n';
        q.push(nxt);
      }
    }
  }
  return 0;
}
