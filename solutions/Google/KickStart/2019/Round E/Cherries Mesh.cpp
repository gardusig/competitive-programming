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
        std::cin >> N >> M;
        for (int i = 0; i < N; i += 1)
        {
            g[i].clear();
        }
        while (M-- > 0)
        {
            int x, y;
            std::cin >> x >> y;
            x -= 1;
            y -= 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }

    void dfs(const int& i, std::vector< bool >& used)
    {
        used[i] = true;
        for (const int& j : g[i])
        {
            if (used[j] == true)
            {
                continue;
            }
            dfs(j, used);
        }
    }

    int solve()
    {
        int components = 0;
        std::vector< bool > used(N, false);
        for (int i = 0; i < N; i += 1)
        {
            if (used[i] == false)
            {
                dfs(i, used);
                components += 1;
            }
        }
        int red = components - 1;
        int black = N - 1 - red;
        return (black * 1) + (red * 2);
    }

    void solveTask(const int& test)
    {
        std::cout << "Case #" << test << ": " << solve() << std::endl;
    }

    int T;
    int N;
    int M;
    std::vector< int > g[112345];
};

int main()
{
    Solution().main();
    return 0;
}