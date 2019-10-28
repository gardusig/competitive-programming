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
        build();
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
        std::cin >> L >> R;
    }

    void build()
    {
        for (int i = 3; i < MAX_SIZE; i += 2)
        {
            if (int(divisors[i].size()) > 0)
            {
                continue;
            }
            divisors[i].insert(i);
            primes.insert(i);
            for (int j = i + i; j < MAX_SIZE; j += i)
            {
                divisors[j].insert(i);
            }
        }
    }

    bool valid(const int& n)
    {
        int current = n;
        std::unordered_map< int, int > factors;
        for (const int& divisor : divisors[n])
        {
            while ((current % divisor) == 0)
            {
                factors[divisor] += 1;
                current /= divisor;
            }
        }
        int even = 0;
        while ((current % 2) == 0)
        {
            even += 1;
            current /= 2;
        }
        if (current > 1)
        {
            factors[current] += 1;
        }
        int odd = 0;
        for (const auto& i : factors)
        {
            odd += (i.second * odd) + i.second;
        }
        even += even * odd;
        odd += 1;
        return abs(even - odd) <= 2;
    }

    int solve()
    {
        for (const int& prime : primes)
        {
            for (int i = std::max(prime, L - (L % prime)); i <= R; i += prime)
            {
                divisors[i].insert(prime);
            }
        }
        int ans = 0;
        for (int i = L; i <= R; i += 1)
        {
            if (valid(i) == true)
            {
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
    int L;
    int R;
    std::set< int > primes;
    std::unordered_map< int, std::unordered_set< int > > divisors;
    const int MAX_SIZE = sqrt(1e9) + 5;
};

int main()
{
    Solution().main();
    return 0;
}