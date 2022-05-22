#include <bits/stdc++.h>

class Math {
 public:
  void build_lowest_factors(const int size) {
    assert(size > 0);
    this->lowest_factors.resize(size);
    for (int i = 2; i < int(lowest_factors.size()); i += 1) {
      lowest_factors[i] = (i & 1) ? i : 2;
    }
    primes.push_back(2);
    for (int prime = 3; prime < int(lowest_factors.size()); prime += 2) {
      if (lowest_factors[prime] != prime) {
        continue;
      }
      primes.push_back(prime);
      for (int multiple = prime; multiple < int(lowest_factors.size());
           multiple += prime) {
        if (lowest_factors[multiple] != multiple) {
          continue;
        }
        lowest_factors[multiple] = prime;
      }
    }
  }

  std::unordered_map<int, int> get_factors(const int N) const {
    assert(N > 0);
    assert(N < int(lowest_factors.size()));
    std::unordered_map<int, int> factors;
    for (int i = N; i > 1; i /= lowest_factors[i]) {
      factors[lowest_factors[i]] += 1;
    }
    return factors;
  }

  std::unordered_map<int64_t, int> get_factors_slow(int64_t N) const {
    assert(N > 0);
    std::unordered_map<int64_t, int> factors;
    for (const int prime : primes) {
      while (N % prime == 0) {
        factors[prime] += 1;
        N /= prime;
      }
      if (N == 1 or N < prime) {
        break;
      }
    }
    if (N > 1) {
      factors[N] += 1;
    }
    return factors;
  }

  std::vector<int> get_primes() const { return this->primes; }

 private:
  std::vector<int> lowest_factors;
  std::vector<int> primes;
};

void validate(const int factor_index, const int64_t prime,
              const std::vector<std::vector<std::pair<int, int>>>& factor_to_c,
              std::vector<int64_t>& C, std::vector<int64_t>& factors) {
  if (factors[factor_index] != -1) {
    return;
  }
  for (const auto& edge : factor_to_c[factor_index]) {
    const int c_index = edge.first;
    const int pot = edge.second;
    int64_t current = 1;
    for (int i = 0; i < pot; i += 1) {
      current *= prime;
      if (C[c_index] % current) {
        return;
      }
    }
  }
  factors[factor_index] = prime;
  for (const auto& edge : factor_to_c[factor_index]) {
    const int c_index = edge.first;
    const int pot = edge.second;
    int64_t current = 1;
    for (int i = 0; i < pot; i += 1) {
      current *= prime;
    }
    C[c_index] /= current;
  }
}

void solve(const int qty_factors, std::vector<int64_t>& C,
           const std::vector<std::vector<std::pair<int, int>>>& factor_to_c) {
  const int64_t max_element = *std::max_element(C.begin(), C.end());
  const int max_size = std::sqrt(max_element) + 1;

  Math math;
  math.build_lowest_factors(max_size);
  const std::vector<int>& primes = math.get_primes();

  std::vector<int64_t> factors(qty_factors, -1);

  for (int i = 0, prime_idx = 0; i < qty_factors; i += 1) {
    if (factors[i] != -1) {
      continue;
    }
    for (int j = prime_idx; j < int(primes.size()); j += 1) {
      const int prime = primes[j];
      validate(i, prime, factor_to_c, C, factors);
      if (factors[i] != -1) {
        prime_idx = j + 1;
        break;
      }
    }
    if (factors[i] == -1) {
      const auto prime = C[factor_to_c[i][0].first];
      validate(i, prime, factor_to_c, C, factors);
      factors[i] = prime;
      prime_idx = primes.size();
    }
  }

  for (const auto i : factors) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

void solve_test_case() {
  int M, N, K;
  std::cin >> M >> N >> K;
  std::vector<int64_t> C(N);
  for (auto& i : C) {
    std::cin >> i;
  }
  std::vector<std::vector<std::pair<int, int>>> factor_to_c(M);
  for (int i = 0; i < K; i += 1) {
    int m, n, d;
    std::cin >> m >> n >> d;
    m -= 1;
    n -= 1;
    factor_to_c[m].push_back({n, d});
  }
  solve(M, C, factor_to_c);
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  solve_test_case();
  return 0;
}
