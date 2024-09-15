#include <bits/stdc++.h>

// Exponentiation by squaring: calculates (base^power) % MOD efficiently.
int exponentiate(int base, int power, const int MOD) {
  int ans = 1;
  while (power > 0) {
    if (power & 1) {
      // Multiply ans by the base when the current bit of power is 1.
      ans = (1LL * ans * base) % MOD;
    }
    // Square the base for the next bit of power.
    base = (1LL * base * base) % MOD;
    power >>= 1;
  }
  return ans;
}

// Build a factorial array: fact[i] = (i!) % MOD for all i < MAX_SIZE.
std::vector<int> build_factorial(const int MAX_SIZE, const int MOD) {
  std::vector<int> fact(MAX_SIZE);
  fact[0] = 1;
  for (int i = 1; i < fact.size(); i += 1) {
    // Use modular arithmetic to calculate the factorial.
    fact[i] = (1LL * fact[i - 1] * i) % MOD;
  }
  return fact;
}

// Build an inverse factorial array: ifact[i] = (i!)^(-1) % MOD for all i <
// MAX_SIZE. Uses Fermat's Little Theorem: a^(MOD-1) ≡ 1 (mod MOD), so a^(MOD-2)
// ≡ a^(-1) (mod MOD).
std::vector<int> build_inverse_factorial(const std::vector<int>& fact,
                                         const int MOD) {
  std::vector<int> ifact(fact.size());
  // The inverse factorial for the largest number is fact[MAX_SIZE-1]^(MOD-2) %
  // MOD.
  ifact.back() = exponentiate(fact.back(), MOD - 2, MOD);
  // Use the property: ifact[i] = ifact[i + 1] * (i + 1) % MOD to build the
  // rest.
  for (int i = ifact.size() - 2; i >= 0; i -= 1) {
    ifact[i] = (1LL * (i + 1) * ifact[i + 1]) % MOD;
  }
  return ifact;
}

// Calculate nCr % MOD using precomputed factorial and inverse factorial arrays.
int combination(const int set_size, const int subset_size,
                const std::vector<int>& fact, const std::vector<int>& ifact,
                const int MOD) {
  if (subset_size < 0 || subset_size > set_size) {
    return 0;
  }
  // Combination formula: nCr = n! / ((n-r)! * r!)
  const int num = fact[set_size];
  const int den =
      (1LL * ifact[set_size - subset_size] * ifact[subset_size]) % MOD;
  return (1LL * num * den) % MOD;
}

// Sieve-like algorithm to build an array of the lowest prime factor (LPF) for
// each number < MAX_SIZE.
std::vector<int> get_lowest_factors(const int MAX_SIZE) {
  std::vector<int> lowest_factors(MAX_SIZE);
  // Initially, mark all even numbers with 2 as their lowest prime factor.
  for (int i = 1; i < lowest_factors.size(); i += 1) {
    lowest_factors[i] = (i & 1) ? i : 2;
  }
  // Use the sieve of Eratosthenes method to find the lowest prime factor for
  // odd numbers.
  for (int prime = 3; prime < lowest_factors.size(); prime += 2) {
    if (lowest_factors[prime] != prime) {
      continue;  // Skip non-prime numbers.
    }
    for (int multiple = prime; multiple < lowest_factors.size();
         multiple += prime) {
      if (lowest_factors[multiple] != multiple) {
        continue;  // Skip numbers that already have a lower prime factor.
      }
      lowest_factors[multiple] =
          prime;  // Set the lowest prime factor for the multiple.
    }
  }
  return lowest_factors;
}

// Decompose a number N into its prime factors using the lowest prime factors
// array (LPF).
std::unordered_map<int, int> get_factors(
    const int N, const std::vector<int>& lowest_factors) {
  std::unordered_map<int, int> factors;
  // Continue dividing N by its lowest prime factor until N becomes 1.
  for (int i = N; i > 1; i /= lowest_factors[i]) {
    factors[lowest_factors[i]] +=
        1;  // Increment the exponent of the prime factor.
  }
  return factors;
}

// Count the number of divisors of N using its prime factorization.
int count_divisors(const int N, const std::vector<int>& lowest_factors) {
  int ans = 1;
  for (const auto& i : get_factors(N, lowest_factors)) {
    ans *= (i.second + 1);  // The number of divisors is the product of
                            // (exponent + 1) for each prime factor.
  }
  return ans;
}

// Build a combination table up to N using dynamic programming.
std::vector<std::vector<int>> combination_build(const int N, const int MOD) {
  std::vector<std::vector<int>> v(N, std::vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    v[i][0] = 1;  // nC0 = 1
    for (int j = 1; j < N; ++j) {
      if (j > i)
        v[i][j] = 0;  // nCr = 0 when r > n
      else
        v[i][j] = (v[i - 1][j - 1] + v[i - 1][j]) % MOD;
      // Pascal's identity: nCr = (n - 1) C(r - 1) + (n - 1) Cr
    }
  }
  return v;
}

// Get the nth element of an arithmetic progression given the start position,
// finish position, and common difference.
int arithmetic_progression_element(const int value, const int pos_start,
                                   const int pos_finish,
                                   const int common_difference) {
  return value + (pos_finish - pos_start) * common_difference;
}

// Get the sum of an arithmetic progression given the first and last values, and
// the number of terms.
int arithmetic_progression_sum(const int value_start, const int value_finish,
                               const int n) {
  return (n * (value_start + value_finish)) / 2;
}

// Get the nth element of a geometric progression (GP) given the start position,
// finish position, and common ratio.
int geometric_progression_element(const int value, const int pos_start,
                                  const int pos_finish, const int common_ratio,
                                  const int MOD) {
  return (1LL * value *
          exponentiate(common_ratio, pos_finish - pos_start, MOD)) %
         MOD;
}

// Get the sum of a geometric progression (GP) given the initial value, common
// ratio, and number of terms.
int geometric_progression_sum(const int value, const int common_ratio,
                              const int n, const int MOD) {
  if (common_ratio == 1) return value * n;
  // Use the formula: sum = a * (1 - r^n) / (1 - r)
  int num =
      (1LL * value * (1 - exponentiate(common_ratio, n, MOD) + MOD)) % MOD;
  int den = (1 - common_ratio + MOD) % MOD;
  // Return the result after calculating the modular inverse of the denominator.
  return (1LL * num * exponentiate(den, MOD - 2, MOD)) % MOD;
}

// Calculate the modular inverse of 'a' % MOD using Fermat's Little Theorem.
// Only works when MOD is prime.
int mod_inverse(int a, const int MOD) { return exponentiate(a, MOD - 2, MOD); }

// Euclidean algorithm to calculate the greatest common divisor (GCD) of two
// numbers.
int gcd(int a, int b) {
  while (b != 0) {
    a %= b;
    std::swap(a, b);
  }
  return a;
}

// Calculate the least common multiple (LCM) of two numbers using their GCD.
int lcm(int a, int b) { return a / gcd(a, b) * b; }

// Euler's Totient Function: Calculates the number of integers from 1 to N
// that are coprime with N.
int euler_totient(int N) {
  int result = N;
  for (int i = 2; i * i <= N; ++i) {
    if (N % i == 0) {
      // Remove all factors of 'i' from N.
      while (N % i == 0) N /= i;
      // Subtract multiples of 'i' from result.
      result -= result / i;
    }
  }
  if (N > 1) result -= result / N;
  return result;
}

// Check if a number N is prime.
bool is_prime(int N) {
  if (N <= 1) return false;
  if (N <= 3) return true;
  if (N % 2 == 0 || N % 3 == 0) return false;
  for (int i = 5; i * i <= N; i += 6) {
    if (N % i == 0 || N % (i + 2) == 0) return false;
  }
  return true;
}

// Extended Euclidean Algorithm: Finds x and y such that a*x + b*y = gcd(a, b)
int extended_gcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int gcd = extended_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return gcd;
}

// Calculate modular inverse of a when MOD is not necessarily prime.
int mod_inverse_extended(int a, int MOD) {
  int x, y;
  int g = extended_gcd(a, MOD, x, y);
  if (g != 1) return -1;  // Inverse doesn't exist if gcd(a, MOD) != 1.
  return (x % MOD + MOD) % MOD;
}

// Calculate nCr % MOD without precomputation of factorials.
int combination_direct(int n, int r, const int MOD) {
  if (r > n) return 0;
  if (r == 0 || r == n) return 1;
  int num = 1, den = 1;
  for (int i = 0; i < r; ++i) {
    num = (1LL * num * (n - i)) % MOD;
    den = (1LL * den * (i + 1)) % MOD;
  }
  return (1LL * num * mod_inverse(den, MOD)) % MOD;
}

void run_tests() {
  const int MOD = 1e9 + 7;

  // Test for exponentiate
  assert(exponentiate(2, 10, MOD) == 1024);

  // Test for build_factorial
  auto fact = build_factorial(6, MOD);
  assert(fact[5] == 120);  // 5! = 120

  // Test for build_inverse_factorial
  auto ifact = build_inverse_factorial(fact, MOD);
  assert(ifact[5] == exponentiate(120, MOD - 2, MOD));
  // Inverse of 5!

  // Test for combination
  assert(combination(5, 2, fact, ifact, MOD) == 10);
  // 5 choose 2 = 10

  // Test for get_lowest_factors
  auto lpf = get_lowest_factors(20);
  assert(lpf[8] == 2);
  // LPF of 8 is 2.

  // Test for get_factors
  auto factors = get_factors(12, lpf);
  assert(factors[2] == 2 && factors[3] == 1);
  // 12 = 2^2 * 3^1

  // Test for count_divisors
  assert(count_divisors(12, lpf) == 6);
  // Divisors of 12 = {1, 2, 3, 4, 6, 12}

  // Test for combination_build
  auto comb_table = combination_build(5, MOD);
  assert(comb_table[4][2] == 6);
  // 4 choose 2 = 6

  // Test for arithmetic_progression_element
  assert(arithmetic_progression_element(3, 0, 4, 2) == 11);
  // 3 + (4 - 0) * 2 = 11

  // Test for arithmetic_progression_sum
  assert(arithmetic_progression_sum(1, 5, 5) == 15);
  // Sum of AP from 1 to 5 with 5 terms.

  // Test for geometric_progression_element
  assert(geometric_progression_element(2, 0, 3, 2, MOD) == 16);
  // 2 * (2^3) = 16

  // Test for geometric_progression_sum
  assert(geometric_progression_sum(1, 2, 4, MOD) == 15);
  // Sum of GP: 1 + 2 + 4 + 8 = 15

  // Test for mod_inverse
  assert(mod_inverse(5, MOD) == exponentiate(5, MOD - 2, MOD));
  // Inverse of 5 mod MOD

  // Test for gcd
  assert(gcd(12, 15) == 3);
  // gcd(12, 15) = 3

  // Test for lcm
  assert(lcm(12, 15) == 60);
  // lcm(12, 15) = 60

  // Test for euler_totient
  assert(euler_totient(9) == 6);
  // Totient(9) = 6 (coprime numbers: 1, 2, 4, 5, 7, 8)

  // Test for is_prime
  assert(is_prime(7) == true && is_prime(9) == false);
  // 7 is prime, 9 is not.

  // Test for extended_gcd
  int x, y;
  assert(extended_gcd(35, 15, x, y) == 5);
  // gcd(35, 15) = 5

  // Test for mod_inverse_extended
  assert(mod_inverse_extended(3, MOD) == exponentiate(3, MOD - 2, MOD));
  // Inverse of 3 mod MOD

  // Test for combination_direct
  assert(combination_direct(5, 2, MOD) == 10);
  // 5 choose 2 = 10

  std::cout << "All tests passed!" << std::endl;
}

int main() {
  run_tests();
  return 0;
}
