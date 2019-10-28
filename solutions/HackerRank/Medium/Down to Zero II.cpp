//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

const int MAX_SIZE = 1123456;

class Solution {
  private:
    int Q;
    int N;

    int used[MAX_SIZE];
    int dist[MAX_SIZE];

    int solve(const int &test, const int &n) {
      queue< int > q;
      q.push(n);
      dist[n] = 0;
      used[n] = test;
      while (q.empty() == false) {
        int i = q.front();
        q.pop();
        if (i == 0) {
          return dist[i];
        }
        unordered_set< int > nxt;
        nxt.insert(i - 1);
        for (int j = 1; 1LL * j * j <= i; j += 1) {
          if ((i % j) != 0) {
            continue;
          }
          nxt.insert(max(j, i / j));
        }
        const int cost = dist[i] + 1;
        for (const int &j: nxt) {
          if (used[j] < test or cost < dist[j]) {
            used[j] = test;
            dist[j] = cost;
            q.push(j);
          }
        }
      }
      return -1;
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }

    void main() {
      cin >> Q;
      for (int i = 0; i < MAX_SIZE; i += 1) {
        used[i] = -1;
      }
      for (int test = 0; test < Q; test += 1) {
        cin >> N;
        cout << solve(test, N) << endl;
      }
    }
};

int main() {
  Solution().main();
  return 0;
}
