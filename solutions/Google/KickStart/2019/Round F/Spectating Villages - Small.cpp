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
            std::cin >> V;
            g.resize(V);
            B.resize(V);
            P.resize(V);
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
            std::cout << "Case #" << test << ": " << solveTask() << std::endl;
        }
    }

private:

    int T;
    int V;
    std::vector< int > B;
    std::vector< int > P;
    std::vector< std::vector< int > > g;
    long long int dp[100000 + 5][2][2];

    long long int solveTask()
    {
        long long int ans = 0;
        for (int i = 0; i < (1 << V); i += 1)
        {
            std::unordered_set< int > current;
            for (int j = 0; j < V; j += 1)
            {
                if (i & (1 << j))
                {
                    current.insert(j);
                    for (const int& k : g[j])
                    {
                        current.insert(k);
                    }
                }
            }
            long long int currentAns = 0;
            for (const int& j : current)
            {
                currentAns += B[j];
            }
            ans = std::max(ans, currentAns);
        }
        return ans;
    }
};

int main()
{
    Solution().main();
    return 0;
}