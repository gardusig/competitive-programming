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
        memset(dp, 0, sizeof dp);
        std::cin >> N >> M;
        for (int i = 0; i < N; i += 1)
        {
            long long int value;
            std::cin >> value;
            for (int j = 0; j < 50; j += 1)
            {
                dp[j][(value & (1LL << j)) ? 1 : 0] += 1;
            }
        }
    }

    long long int solve()
    {
        long long int mn = 0;
        for (int i = 0; i < 50; i += 1)
        {
            mn += (1LL << i) * std::min(dp[i][0], dp[i][1]);
        }
        if (mn > M)
        {
            return -1;
        }
        long long int ans = 0;
        long long int sum = 0;
        for (int bit = 49; bit >= 0; bit -= 1)
        {
            long long int current = sum + ((1LL << bit) * dp[bit][0]);
            for (int i = 0; i < bit; i += 1)
            {
                current += (1LL << i) * std::min(dp[i][0], dp[i][1]);
            }
            if (current <= M)
            {
                ans |= (1LL << bit);
                sum += ((1LL << bit) * dp[bit][0]);
            }
            else
            {
                sum += ((1LL << bit) * dp[bit][1]);
            }
        }
        return ans;
    }

    void solveTask(const int& test)
    {
        std::cout << "Case #" << test << ": " << solve() << std::endl;
    }

    int T;
    int N;
    long long int M;
    std::vector< long long int > v;
    int dp[60][2];
};

int main()
{
    Solution().main();
    return 0;
}