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
        readTask();
        solveTask();
    }

private:

    void readTask()
    {
        std::cin >> N;
        std::cin >> K;
        v.resize(N);
        for (int& i : v)
        {
            std::cin >> i;
        }
    }

    void solveTask()
    {
        sort(v.begin(), v.end());
        std::vector< long long int > sum(N);
        sum[0] = v[0];
        for (int i = 1; i < N; i += 1)
        {
            sum[i] = sum[i - 1] + v[i];
        }
        long long int ans = 0;
        for (int i = 0; i < K; i += 1)
        {
            ans += (sum[K - 1] - sum[i]) - (1LL * (K - i - 1) * v[i]);
        }
        long long int current = ans;
        for (int i = K; i < N; i += 1)
        {
            current -= (sum[i - 1] - sum[i - K]) - (1LL * (K - 1) * v[i - K]);
            current += (1LL * (K - 1) * v[i]) - (sum[i - 1] - sum[i - K]);
            ans = std::min(ans, current);
        }
        std::cout << ans << std::endl;
    }

    int N;
    int K;
    std::vector< int > v;
};

int main()
{
    Solution().main();
    return 0;
}