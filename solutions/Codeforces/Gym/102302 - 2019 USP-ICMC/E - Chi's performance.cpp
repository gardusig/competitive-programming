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

  void build()
  {
    memset(dp, -1, sizeof dp);
    int idx = -1;
    for (auto& i : people)
    {
      idx += 1;
      std::sort(i.second.begin(), i.second.end());
      if (int(i.second.size()) < 4)
      {
        v[idx] = i.second;
      }
      else
      {
        v[idx].push_back(i.second[0]);
        v[idx].push_back(i.second[1]);
        v[idx].push_back(i.second[int(i.second.size()) - 1]);
        v[idx].push_back(i.second[int(i.second.size()) - 2]);
      }
    }
  }

  long long int solve(const int& i, const int& last)
  {
    if (dp[i][last] != -1)
    {
      return dp[i][last];
    }
    if (i == int(people.size()))
    {
      dp[i][last] = 0;
      return dp[i][last];
    }
    long long int ans = 0;
    if (int(v[i].size()) == 1)
    {
      if (i > 0)
      {
        ans += std::abs(v[i][0] - v[i - 1][last]);
      }
      ans += solve(i + 1, 0);
    }
    else
    {
      for (int l = 0; l < int(v[i].size()); l += 1)
      {
        long long int current = 0;
        if (i > 0)
        {
          current += std::abs(v[i][l] - v[i - 1][last]);
        }
        long long int nxt = 0;
        for (int r = 0; r < int(v[i].size()); r += 1)
        {
          if (l == r)
          {
            continue;
          }
          nxt = std::max(nxt, solve(i + 1, r));
        }
        ans = std::max(ans, current + nxt);
      }
    }
    dp[i][last] = ans;
    return dp[i][last];
  }

  void main()
  {
    std::cin >> N;
    for (int i = 0; i < N; i += 1)
    {
      int V, P;
      std::cin >> V >> P;
      people[V].push_back(P);
    }
    build();
    std::cout << solve(0, 0) << std::endl;
  }

private:
  static const int MAX_SIZE = 1000000 + 5;
  int N;
  std::map< int, std::vector< int > > people;
  long long int dp[MAX_SIZE][4];
  std::vector< int > v[MAX_SIZE];
};

int main()
{
  Solution().main();
  return 0;
}