#include <bits/stdc++.h>

namespace KMP {

const int N = 1e6 + 5;

int kmp[N];

// Function to build the KMP (Knuth-Morris-Pratt) table
void buildKMP(const std::string& pattern) {
  std::fill(kmp, kmp + N, 0);  // Clear the kmp array to avoid residual values
  kmp[0] = 0;
  for (int i = 1, j = 0; i < pattern.size(); ++i) {
    while (j && pattern[i] != pattern[j]) j = kmp[j - 1];
    if (pattern[i] == pattern[j]) ++j;
    kmp[i] = j;
  }
}

// Function to query the number of occurrences of the pattern in the text
int query(const std::string& pattern, const std::string& text) {
  int ans = 0;
  int m = pattern.size();
  int n = text.size();

  for (int i = 0, j = 0; i < n; ++i) {
    while (j && text[i] != pattern[j]) j = kmp[j - 1];
    if (text[i] == pattern[j] && ++j == m) {
      ++ans;
      j = kmp[j - 1];
    }
  }
  return ans;
}

}  // namespace KMP

void testKMP() {
  std::string pattern;

  pattern = "abc";
  KMP::buildKMP(pattern);
  assert(KMP::query(pattern, "ababcababcabc") == 3);

  pattern = "abcd";
  KMP::buildKMP(pattern);
  assert(KMP::query(pattern, "abcdabcdabcabcdabcd") == 4);

  std::cout << "All KMP tests passed!" << std::endl;
}

int main() {
  testKMP();
  return 0;
}
