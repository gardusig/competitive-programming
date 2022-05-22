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
        std::cin >> T;
        for (int test = 1; test <= T; test += 1)
        {
            readTask();
            solveTask(test);
        }
    }

private:

    void readTask()
    {
        std::cin >> V;
        B.resize(V);
        g.resize(V);
        for (int i = 0; i < V; i += 1)
        {
            g[i].clear();
            std::cin >> B[i];
        }
        for (int i = 1; i < V; i += 1)
        {
            int x, y;
            std::cin >> x >> y;
            x -= 1;
            y -= 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }

    long long int solve(const int& i, const int& p, const bool& flag, const bool& parentFlag)
    {
        if (dpAll[i][flag][parentFlag] != -1)
        {
            return dpAll[i][flag][parentFlag];
        }
        if (parentFlag == true or flag == true)
        {
            long long int ans = B[i];
            for (const int& j : g[i])
            {
                if (j == p)
                {
                    continue;
                }
                const auto& kappa = solve(j, i, true, flag);
                const auto& keepo = solve(j, i, false, flag);
                ans += std::max(kappa, keepo);
            }
            return dpAll[i][flag][parentFlag] = ans;
        }
        else
        {
            std::vector< long long int > dp[2];
            dp[0].push_back(0);
            dp[1].push_back(-1e15);
            for (const int& j : g[i])
            {
                if (j == p)
                {
                    continue;
                }
                const auto& kappa = solve(j, i, true, flag);
                const auto& keepo = solve(j, i, false, flag);
                dp[1].push_back
                (
                    std::max
                    (
                        dp[0].back() + kappa,
                        dp[1].back() + std::max(kappa, keepo)
                    )
                );
                dp[0].push_back(dp[0].back() + keepo);
            }
            return dpAll[i][flag][parentFlag] = std::max(dp[0].back(), dp[1].back() + B[i]);
        }
    }

    void solveTask(const int& test)
    {
        long long int ans = 0;
        memset(dpAll, -1, sizeof dpAll);
        ans = std::max(ans, solve(0, -1, true, false));
        ans = std::max(ans, solve(0, -1, false, false));
        std::cout << "Case #" << test << ": " << ans << std::endl;
    }

    int T;
    int V;
    std::vector< int > B;
    long long int dpAll[112345][2][2];
    std::vector< std::vector< int > > g;
};

int main()
{
    Solution().main();
    return 0;
}