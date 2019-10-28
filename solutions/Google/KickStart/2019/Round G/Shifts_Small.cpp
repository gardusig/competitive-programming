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
        std::cin >> N >> H;
        A.resize(N);
        for (int& i : A)
        {
            std::cin >> i;
        }
        B.resize(N);
        for (int& i : B)
        {
            std::cin >> i;
        }
    }

    long long int solve()
    {
        long long int ans = 0;
        for (int maskA = 0; maskA < (1 << N); maskA += 1)
        {
            long long int currentA = 0;
            for (int i = 0; i < N; i += 1)
            {
                if (maskA & (1 << i))
                {
                    currentA += A[i];
                }
            }
            if (currentA < H)
            {
                continue;
            }
            for (int maskB = 0; maskB < (1 << N); maskB += 1)
            {
                if ((maskA | maskB) + 1 != (1 << N))
                {
                    continue;
                }
                long long int currentB = 0;
                for (int i = 0; i < N; i += 1)
                {
                    if (maskB & (1 << i))
                    {
                        currentB += B[i];
                    }
                }
                if (currentB < H)
                {
                    continue;
                }
                ans += 1;
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
    int H;
    std::vector< int > A;
    std::vector< int > B;
};

int main()
{
    Solution().main();
    return 0;
}