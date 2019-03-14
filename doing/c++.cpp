#include <bits/stdc++.h>
using namespace std;

vector<int> IDsOfPackages(int truckSpace, vector<int> packagesSpace) {
  vector< pair< int, int > > v;
  for (int i = 0; i < int(packagesSpace.size()); i += 1) {
    v.push_back({packagesSpace[i], i});
    assert(packagesSpace[i] >= 0);
  }
  sort(v.rbegin(), v.rend());
  for (int i = 0; i < int(v.size()) - 1; i += 1) {
    int idx = -1;
    int lo = i + 1;
    int hi = int(v.size()) - 1;
    int have = truckSpace - 30 - v[i].first;
    if (have < 0) {
      continue;
    }
    while (lo <= hi) {
      const auto mid = lo + ((hi - lo) / 2);
      if (v[mid].first > have) {
        lo = mid + 1;
      } else {
        idx = mid;
        hi = mid - 1;
      }
    }
    if (idx != -1) {
      vector< int > ans = {v[i].second, v[idx].second};
      sort(ans.begin(), ans.end());
      return ans;
    }
  }
  return vector< int >(2, -1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  vector< int > v = {0, 0, 1, 2, 3};
  for (const auto &i: IDsOfPackages(33, v)) {
    cout << i << ' ' ;
  }
  cout << endl;
  return 0;
}