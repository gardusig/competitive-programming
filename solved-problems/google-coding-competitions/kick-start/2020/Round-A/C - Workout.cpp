#include <climits>
#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;

    for (int test = 1; test <= T; test += 1)
    {
        int N, K;
        std::cin >> N >> K;

        std::vector<int> V(N);
        for (int &i : V)
        {
            std::cin >> i;
        }

        int lo = 1;
        int hi = INT_MAX;
        while (lo <= hi)
        {
            const int mid = lo + ((hi - lo) >> 1);

            int current = 0;

            for (int i = 1; i < N; i += 1)
            {
                const int diff = V[i] - V[i - 1];
                if (diff <= mid)
                {
                    continue;
                }
                current += ((diff + mid - 1) / mid) - 1;
            }

            if (current > K)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }

        std::cout << "Case #" << test << ": " << hi + 1 << std::endl;
    }

    return 0;
}