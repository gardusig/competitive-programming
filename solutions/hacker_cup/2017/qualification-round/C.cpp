#include <bits/stdc++.h>

struct Spell {
  int rolls;
  int sides;
  int modifier;

  Spell(const std::string& spell) {
    size_t dPos = spell.find('d');
    size_t plusPos = spell.find('+');
    size_t minusPos = spell.find('-');
    rolls = std::stoi(spell.substr(0, dPos));
    if (plusPos != std::string::npos) {
      sides = std::stoi(spell.substr(dPos + 1, plusPos - dPos - 1));
      modifier = std::stoi(spell.substr(plusPos));
    } else if (minusPos != std::string::npos) {
      sides = std::stoi(spell.substr(dPos + 1, minusPos - dPos - 1));
      modifier = std::stoi(spell.substr(minusPos));
    } else {
      sides = std::stoi(spell.substr(dPos + 1));
      modifier = 0;
    }
  }
};

double computeProbability(int H, const std::string& spell) {
  Spell parsedSpell(spell);
  int rolls = parsedSpell.rolls;
  int sides = parsedSpell.sides;
  int modifier = parsedSpell.modifier;
  int maxSum = rolls * sides;
  std::vector<double> dp(maxSum + 1, 0.0);
  dp[0] = 1.0;
  for (int i = 0; i < rolls; ++i) {
    std::vector<double> newDp(maxSum + 1, 0.0);
    for (int sum = 0; sum <= i * sides; ++sum) {
      if (dp[sum] > 0) {
        for (int outcome = 1; outcome <= sides; ++outcome) {
          newDp[sum + outcome] += dp[sum] / sides;
        }
      }
    }
    dp = newDp;
  }
  double probability = 0.0;
  for (int sum = H - modifier; sum <= maxSum; ++sum) {
    if (sum >= 0 && sum <= maxSum) {
      probability += dp[sum];
    }
  }
  return probability;
}

void processTestCase() {
  int H, S;
  std::cin >> H >> S;
  std::vector<std::string> spells(S);
  for (int i = 0; i < S; ++i) {
    std::cin >> spells[i];
  }
  double maxProbability = 0.0;
  for (const auto& spell : spells) {
    double probability = computeProbability(H, spell);
    maxProbability = std::max(maxProbability, probability);
  }
  std::cout << std::fixed << std::setprecision(6) << maxProbability
            << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int tests;
  std::cin >> tests;
  for (int testCase = 1; testCase <= tests; testCase += 1) {
    std::cout << "Case #" << testCase << ": ";
    processTestCase();
  }
}
