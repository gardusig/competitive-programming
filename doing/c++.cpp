#include <bits/stdc++.h>
using namespace std;

vector<int> cellCompete(int* states, int days) {
  int size = 2 + (sizeof(states) / sizeof(states[0]));
  vector< int > ans(size, 0), before(size, 0);
  for (int i = 1; i < size - 1; i += 1) {
    before[i] = states[i - 1];
  }
  for (int i = 0; i < days; i += 1) {
    for (int j = 1; j < size - 1; j += 1) {
      ans[j] = !(before[j - 1] == before[j + 1]);
    }
    before = ans;
  }
  ans.erase(ans.begin());
  ans.erase(ans.end() - 1);
  return ans;
}

int main() {
  int states[] = {1, 0, 0, 0, 0, 1, 0, 0};
  for (int days = 1; days <= 100; days += 1) {
    for (const auto &i: cellCompete(states, days)) {
      cout << i << ' ';
    }
    cout << endl;
  }
  return 0;
}