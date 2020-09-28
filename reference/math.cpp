#include <bits/stdc++.h>

std::vector<int> build_lowest_divisors(const int MAX_SIZE) {
  std::vector<int> lowest_divisors{MAX_SIZE};
  for (int i = 0; i < MAX_SIZE; ++i) {
    lowest_divisors[i] = (i & 1) ? i : 2;
  }
  for (int prime = 3; prime < MAX_SIZE; prime += 2) {
    if (lowest_divisors[prime] != prime) {
      continue;
    }
    for (int multiple = prime; multiple < MAX_SIZE; multiple += prime) {
      if (lowest_divisors[multiple] == prime) {
        lowest_divisors[multiple] = prime;
      }
    }
  }
  return lowest_divisors;
}

std::vector<int> get_factors(const int N,
                             const std::vector<int> &lowest_divisors) {
  std::vector<int> factors;
  for (int i = N; i > 0; i /= lowest_divisors[i]) {
    factors.push_back(lowest_divisors[i]);
  }
  return factors;
}

int count_divisors(const int N, const std::vector<int> &lowest_divisors) {
  std::unordered_map<int, int> frequency;
  for (const int factor : get_factors(N, lowest_divisors)) {
    frequency[factor] += 1;
  }
  int ans = 1;
  for (const auto &i : frequency) {
    ans *= (i.second + 1);
  }
  return ans;
}

std::vector<int> build_factorial(const int MAX_SIZE, const int MOD) {
  std::vector<int> fact{MAX_SIZE};
  fact[0] = 1;
  for (int i = 1; i < fact.size(); i += 1) {
    fact[i] = (1LL * fact[i - 1] * i) % MOD;
  }
  return fact;
}

int fast_exponentiate(int base, int power, const int MOD) {
  int ans = 1;
  while (power > 0) {
    if (power & 1) {
      ans = (1LL * ans * base) % MOD;
    }
    base = (1LL * base * base) % MOD;
    power >>= 1;
  }
  return ans;
}

std::vector<int> build_inverse_factorial(const std::vector<int> &fact,
                                         const int MOD) {
  const int MAX_SIZE{fact.size()};
  std::vector<int> fact_inv{MAX_SIZE};
  fact_inv[MAX_SIZE - 1] = fast_exponentiate(fact[MAX_SIZE], MOD - 2, MOD);
  for (int i = MAX_SIZE - 2; i >= 0; i -= 1) {
    fact_inv[i] = (1LL * (i + 1) * fact_inv[i + 1]) % MOD;
  }
  return fact_inv;
}

int combination(const auto &n, const auto &k, const auto &MOD, const auto &fat,
                const auto &inv_fat) {
  int den = (1LL * inv_fat[k] * inv_fat[n - k]) % MOD;
  return (1LL * fat[n] * den) % MOD;
}

vector<vector<int> > combination_build(const auto &N, const auto &MOD) {
  vector<vector<int> > v;
  v.resize(N);
  for (int i = 0; i < int(v.size()); ++i) v[i].resize(N);
  for (int i = 0; i < N; ++i) {
    v[i][0] = 1;
    for (int j = 1; j < N; ++j) {
      if (j > i)
        v[i][j] = 0;
      else
        v[i][j] = (v[i - 1][j - 1] + v[i - 1][j]) % MOD;
    }
  }
  return v;
}

int arithmetic_progression_element(const auto &value, const auto &pos_start,
                                   const auto &pos_finish,
                                   const auto &common_difference) {
  return value + (pos_finish - pos_start) * common_difference;
}

int arithmetic_progression_sum(const auto &value_start,
                               const auto &value_finish, const auto &n) {
  return (n * (value_start + value_finish)) >> 1;
}

int geometric_progression_element(const auto &value, const auto &pos_start,
                                  const auto &pos_finish,
                                  const auto &common_ratio, const auto &MOD) {
  return value * exponentiate(common_ratio, pos_finish - pos_start, MOD);
}

int geometric_progression_sum(const auto &value, const auto &common_ratio,
                              const auto &n) {
  int num = value * (1 - pow(common_ratio, n));
  int den = (1 - common_ratio);
  return num / den;
}

double simple_interest(const auto &capital, const auto &percentage,
                       const auto &qtd) {
  return capital * (1.0 + (percentage * qtd));
}

double compound_interest(const auto &capital, const auto &percentage,
                         const auto &qtd) {
  return capital * pow(1.0 + percentage, qtd);
}

int main() { return 0; }