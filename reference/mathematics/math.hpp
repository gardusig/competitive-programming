#include <bits/stdc++.h>

namespace math {
std::vector<int> build_lowest_divisors(const int MAX_SIZE);
std::vector<int> get_factors(const int N,
                             const std::vector<int> &lowest_divisors);
int count_divisors(const int N, const std::vector<int> &lowest_divisors);
std::vector<int> build_factorial(const int MAX_SIZE, const int MOD);
int fast_exponentiate(int base, int power, const int MOD);
std::vector<int> build_inverse_factorial(const std::vector<int> &fact,
                                         const int MOD);
};  // namespace math