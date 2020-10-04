#include <bits/stdc++.h>

std::mt19937 rng(int(std::chrono::steady_clock::now().time_since_epoch().count()));

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
        std::vector< int > v;
        std::shuffle(v.begin(), v.end(), rng);
    }

private:


};

int main()
{
    Solution().main();
    return 0;
}