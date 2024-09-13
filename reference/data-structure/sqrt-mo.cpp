#include <bits/stdc++.h>

namespace mo {

template <typename T, typename UpdateAdd, typename UpdateRemove>
class MoAlgorithm {
 private:
  int n, q, block_size;
  std::vector<T> arr;
  UpdateAdd addFunc;
  UpdateRemove removeFunc;
  std::vector<int> answer;
  T current_answer;

  static bool cmp(const std::pair<std::pair<int, int>, int>& a,
                  const std::pair<std::pair<int, int>, int>& b,
                  int block_size) {
    int block_a = a.first.first / block_size;
    int block_b = b.first.first / block_size;
    if (block_a == block_b) {
      return (block_a & 1) ? (a.first.second < b.first.second)
                           : (a.first.second > b.first.second);
    }
    return block_a < block_b;
  }

 public:
  MoAlgorithm(const std::vector<T>& input_array, UpdateAdd add,
              UpdateRemove remove)
      : arr(input_array), addFunc(add), removeFunc(remove) {
    n = int(arr.size());
    block_size = sqrt(n);
    current_answer = T();
  }

  std::vector<T> process(
      std::vector<std::pair<std::pair<int, int>, int>>& queries) {
    q = int(queries.size());
    answer.resize(q);
    std::sort(queries.begin(), queries.end(),
              [this](const std::pair<std::pair<int, int>, int>& a,
                     const std::pair<std::pair<int, int>, int>& b) {
                return cmp(a, b, block_size);
              });
    int L = 0, R = -1;
    for (const auto& query : queries) {
      int l = query.first.first;
      int r = query.first.second;
      int query_id = query.second;
      while (R < r) addFunc(++R, current_answer);
      while (R > r) removeFunc(R--, current_answer);
      while (L < l) removeFunc(L++, current_answer);
      while (L > l) addFunc(--L, current_answer);
      answer[query_id] = current_answer;
    }
    return answer;
  }
};
}  // namespace mo

int main() {
  std::vector<int> A = {0, 1, 2, 3, 0, 1};
  std::vector<int> freq(10, 0);
  int maxFrequency = 0;

  auto add = [&](int idx, int& maxFrequency) {
    int value = A[idx];
    freq[value]++;
    maxFrequency = std::max(maxFrequency, freq[value]);
  };

  auto remove = [&](int idx, int& maxFrequency) {
    int value = A[idx];
    freq[value]--;
    if (freq[maxFrequency] == 0) {
      maxFrequency--;
    }
    while (maxFrequency > 0 && freq[maxFrequency] == 0) {
      maxFrequency--;
    }
  };

  std::vector<std::pair<std::pair<int, int>, int>> queries = {
      {{0, 3}, 0}, {{1, 5}, 1}, {{0, 5}, 2}, {{2, 4}, 3}};

  mo::MoAlgorithm<int, decltype(add), decltype(remove)> mo_algo(A, add, remove);
  std::vector<int> results = mo_algo.process(queries);

  for (int i = 0; i < results.size(); i++) {
    std::cout << "Result of query " << i + 1 << ": " << results[i] << std::endl;
  }
  return 0;
}
