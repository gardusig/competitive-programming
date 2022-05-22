#include <bits/stdc++.h>

long long solve(const int N, const int M, const int F)
{
    std::vector<long long> accum_dp(N + 5);
    std::vector<long long> dp(N + 5, 0);
    std::vector<long long> new_dp(N + 5);

    for (int i = 1; i <= M; i += 1)
    {
        dp[i] = 1;
    }
    for (int factors = 2; factors <= F; factors += 1)
    {
        accum_dp[0] = 0;
        for (int i = 0; i <= N; i += 1)
        {
            accum_dp[i + 1] = accum_dp[i] + dp[i];
        }

        for (int sum = 0; sum <= N; sum += 1)
        {
            new_dp[sum] = accum_dp[sum] - accum_dp[std::max(0, sum - M)];
        }
        dp = new_dp;
    }

    return dp[N];
}

int main()
{
    int N, M;
    std::cin >> N >> M;

    std::cout << solve(N, M, 3) << std::endl;

    return 0;
}