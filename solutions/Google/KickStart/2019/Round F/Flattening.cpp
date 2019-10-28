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
            std::cin >> N >> K;
            A.resize(N);
            for (int& i : A)
            {
                std::cin >> i;
            }
            std::cout << "Case #" << test << ": " << solveTask() << std::endl;
        }
    }

private:

    int T;
    int N;
    int K;
    std::vector< int > A;
    int dp[112][112][112];

    int solve(const int& i, const int& j, const int& k)
    {
        if (dp[i][j][k] != -1)
        {
            return dp[i][j][k];
        }
        if (i == N + 1)
        {
            dp[i][j][k] = 0;
            return dp[i][j][k];
        }
        int ans = solve(i + 1, j, k) + 1;
        if (k < K)
        {
            ans = std::min(ans, solve(i + 1, i, k + 1));
        }
        if (j == 0 or A[i - 1] == A[j - 1])
        {
            ans = std::min(ans, solve(i + 1, i, k));
        }
        dp[i][j][k] = ans;
        return dp[i][j][k];
    }

    int solveTask()
    {
        memset(dp, -1, sizeof dp);
        return solve(1, 0, 0);
    }
};

int main()
{
    Solution().main();
    return 0;
}