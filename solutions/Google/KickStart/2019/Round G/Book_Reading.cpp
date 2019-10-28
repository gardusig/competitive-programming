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
        std::cin >> N >> M >> Q;
        invalid.resize(M);
        for (int& i : invalid)
        {
            std::cin >> i;
        }
        query.resize(Q);
        for (int& i : query)
        {
            std::cin >> i;
        }
    }

    long long int solve()
    {
        std::vector< int > bad(N + 1, 0);
        for (const int& i : invalid)
        {
            for (int j = 1; 1LL * j * j <= i; j += 1)
            {
                if ((i % j) == 0)
                {
                    bad[j] += 1;
                    if ((i / j) != j)
                    {
                        bad[i / j] += 1;
                    }
                }
            }
        }
        long long int ans = 0;
        for (const int& q : query)
        {
            ans += (N / q) - bad[q];
        }
        return ans;
    }

    void solveTask(const int& test)
    {
        std::cout << "Case #" << test << ": " << solve() << std::endl;
    }

    int T;
    int N;
    int M;
    int Q;
    std::vector< int > query;
    std::vector< int > invalid;
};

int main()
{
    Solution().main();
    return 0;
}