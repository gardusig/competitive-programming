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
        int T;
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
        std::cin >> N >> S;
        g.resize(N);
        for (int i = 0; i < N; i += 1)
        {
            g[i].clear();
            int C;
            std::cin >> C;
            while (C-- > 0)
            {
                int skill;
                std::cin >> skill;
                skill -= 1;
                g[i].emplace_back(skill);
            }
        }
    }

    void solveTask(const int& test)
    {
        dp.clear();
        for (int i = 0; i < N; i += 1)
        {
            std::sort(g[i].begin(), g[i].end());
            dp[g[i]] += 1;
        }
        long long int ans = 1LL * N * N;
        for (const auto& skills : g)
        {
            std::vector< int > current;
            for (int mask = 0; mask < (1 << int(skills.size())); mask += 1)
            {
                current.clear();
                for (int i = 0; i < int(skills.size()); i += 1)
                {
                    if (mask & (1 << i))
                    {
                        current.emplace_back(skills[i]);
                    }
                }
                ans -= dp[current];
            }
        }
        std::cout << "Case #" << test << ": " << ans << std::endl;
    }

    int N;
    int S;
    std::vector< std::vector< int > > g;
    std::map< std::vector< int >, int > dp;
};

int main()
{
    Solution().main();
    return 0;
}