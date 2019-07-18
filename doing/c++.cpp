//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

class Ladder {
  public:
    int x, a, b;

    Ladder(const int &x, const int &a, const int &b) {
      this->x = x;
      this->a = a;
      this->b = b;
    }

    bool operator < (const Ladder &other) {
      return this->x < other.x;
    }
};

class Solution {
  private:
    int N, H;
    vector< Ladder > ladders;

    void buildGraph() {
      sort(ladders.begin(), ladders.end());
      for (int i = 0; i < N; i += 1) {
        vector< pair< int, int > > current;
        for (int j = 0; j < N; j += 1) {
          if (ladders[j].x > ladders[i].x) {
            current.emplace_back(ladders[j].a, j);
            current.emplace_back(ladders[j].b, j);
          }
        }
        sort(current.begin(), current.end());
        int lastY = INT_MIN;
        unordered_set< int > used;
        priority_queue< pair< int, int > > pq;
        for (const pair< int, int > &j: current) {
          const int &currentY = j.first;
          const Ladder &ladder = ladders[j.second];
          if (pq.empty() == false and ladder.x <= pq.top().first) {
            int low = max(1, max(lastY, ladders[i].a));
            int high = min(H - 1, min(currentY, ladders[i].b));
            if (low < high) {
              cout << j.second << ' ' << pq.top().second << " -> " << high - low << endl;
            }
          }
          if (used.count(j.second) == 0) {
            pq.emplace(ladder.x, j.second);
          } else {
            //~ pq.pop(ladder.x, j.second);
          }
          lastY = currentY;
        }
      }
    }

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }

    void main() {
      int t;
      cin >> t;
      while (t-- > 0) {
        cin >> N >> H;
        ladders.clear();
        for (int i = 0; i < N; i += 1) {
          int x, a, b;
          cin >> x >> a >> b;
          ladders.emplace_back(x, a, b);
        }
        buildGraph();
      }
    }
};

int main() {
  Solution().main();
  return 0;
}