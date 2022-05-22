#include <bits/stdc++.h>

template <typename T>
class FenwickTree {
 public:
  FenwickTree(const int size) : accum(size, 0) {}

  void clear() { std::fill(accum.begin(), accum.end(), 0); }

  void resize(const int size) {
    if (size < 0) {
      assert(false);
    }
    this->accum.resize(size);
  }

  T query(const int idx) const {
    if (idx >= static_cast<int>(this->accum.size())) {
      assert(false);
    }
    T ans = 0;
    for (int i = idx; i > 0; i -= i & (-i)) {
      ans += this->accum[i];
    }
    return ans;
  }

  void update(const int idx, const T value) {
    if (idx <= 0) {
      assert(false);
    }
    if (idx >= static_cast<int>(accum.size())) {
      assert(false);
    }
    for (int i = idx; i < static_cast<int>(accum.size()); i += i & (-i)) {
      this->accum[i] += value;
    }
  }

 private:
  std::vector<T> accum;
};

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int Y, N;
  std::cin >> Y >> N;

  std::vector<int> YEARS(Y);

  // <slots, year>
  std::vector<std::pair<int, int>> slots;
  for (int i = 0; i < Y; i += 1) {
    int X;
    std::cin >> X;
    slots.push_back({X, i + 1});
    YEARS[i] = X;
  }
  std::sort(slots.rbegin(), slots.rend());

  std::vector<bool> unhappy(N, true);

  // <position, <<start, finish>, person_idx>
  std::vector<std::pair<int, std::pair<std::pair<int, int>, int>>> people;
  for (int i = 0; i < N; i += 1) {
    int A, P, F;
    std::cin >> A >> P >> F;
    people.push_back({P, {{A + 1, A + F}, i}});
    if (P <= YEARS[A - 1]) {
      unhappy[i] = false;
    }
  }
  std::sort(people.rbegin(), people.rend());

  FenwickTree<int> bit(312345);
  std::vector<int> ans(N, -1);

  int person_idx = 0;
  for (const auto& slot : slots) {
    const int position = slot.first;
    const int year = slot.second;

    while (person_idx < int(people.size())) {
      if (people[person_idx].first <= position) {
        break;
      }

      const int start = people[person_idx].second.first.first;
      const int finish = people[person_idx].second.first.second;
      const int idx = people[person_idx].second.second;

      ans[idx] = bit.query(finish) - bit.query(start - 1);

      person_idx += 1;
    }

    bit.update(year, 1);
  }

  while (person_idx < int(people.size())) {
    const int start = people[person_idx].second.first.first;
    const int finish = people[person_idx].second.first.second;
    const int idx = people[person_idx].second.second;

    ans[idx] = bit.query(finish) - bit.query(start - 1);

    person_idx += 1;
  }

  for (int i = 0; i < N; i += 1) {
    if (unhappy[i] == false) {
      ans[i] = 0;
    }
  }

  for (const int i : ans) {
    std::cout << i << '\n';
  }

  return 0;
}
