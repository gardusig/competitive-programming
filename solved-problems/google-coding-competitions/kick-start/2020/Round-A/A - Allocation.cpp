#include <algorithm>
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
        int N, B;
        std::cin >> N >> B;

        std::vector<int> V(N);

        for (int &i : V)
        {
            std::cin >> i;
        }

        std::sort(V.begin(), V.end());

        int ans = 0;
        for (const int i : V)
        {
            if (i > B)
            {
                break;
            }
            ans += 1;
            B -= i;
        }
        std::cout << "Case #" << test << ": " << ans << std::endl;
    }

    return 0;
}