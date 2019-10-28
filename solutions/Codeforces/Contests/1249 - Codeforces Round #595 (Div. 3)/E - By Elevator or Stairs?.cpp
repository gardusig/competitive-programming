#include <bits/stdc++.h>

class Solution
{
public:
  Solution()
  {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
  }

  void main()
  {
    std::cin >> N >> C;
    A.resize(N - 1);
    for (int& i : A)
    {
      std::cin >> i;
    }
    B.resize(N - 1);
    for (int& i : B)
    {
      std::cin >> i;
    }
    solve();
    for (int i = 0; i < N; i += 1)
    {
      std::cout << std::min(dp[i][0], dp[i][1]) << ' ';
    }
    std::cout << std::endl;
  }

private:
  int N;
  int C;
  std::vector< int > A;
  std::vector< int > B;
  int dp[212345][2];

  void solve()
  {
    dp[0][0] = 0;
    dp[0][1] = INT_MAX;
    for (int i = 0; i < N - 1; i += 1)
    {
      dp[i + 1][0] = std::min(dp[i][0], dp[i][1]) + A[i];
      dp[i + 1][1] = std::min(dp[i][0] + C, dp[i][1]) + B[i];
    }
  }
};

int main()
{
  Solution().main();
  return 0;
}