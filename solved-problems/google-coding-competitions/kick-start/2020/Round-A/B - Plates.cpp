#include <climits>
#include <cstring>
#include <iostream>

int N, K, P;
int V[51][31];
int dp[51][31][51 * 31];

int solve(const int i, const int j, const int k)
{
    if (dp[i][j][k] != -1)
    {
        return dp[i][j][k];
    }
    if (i == N)
    {
        return dp[i][j][k] = (k ? INT_MIN : 0);
    }
    int ans = solve(i + 1, 0, k);
    if (j < K and k > 0)
    {
        ans = std::max(ans, solve(i, j + 1, k - 1) + V[i][j]);
    }
    return dp[i][j][k] = ans;
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;

    for (int test = 1; test <= T; test += 1)
    {        
        std::cin >> N >> K >> P;

        for (int i = 0; i < N; i += 1)
        {
            for (int j = 0; j < K; j += 1)
            {
                std::cin >> V[i][j];
            }
        }

        std::memset(dp, -1, sizeof dp);
        std::cout << "Case #" << test << ": " << solve(0, 0, P) << std::endl;
    }

    return 0;
}