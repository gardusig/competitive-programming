#include <iostream>
#include <vector>
#include <cassert>

const int LIMIT = 50;

void solve_test_case()
{
    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> ans;

    if (N < LIMIT)
    {
        for (int i = 0; i < N; i += 1)
        {
            std::cout << i + 1 << " " << 1 << std::endl;
        }
        return;
    }

    N -= LIMIT;
    int side = 0;

    int to_do = 0;

    std::cout << 1 << " " << 1 << std::endl;
    for (int i = 1; i < LIMIT; i += 1)
    {
        if (N & (1LL << i))
        {
            if (side)
            {
                for (int j = i; j >= 0; j -= 1)
                {
                    std::cout << i + 1 << " " << j + 1 << std::endl;
                }
            }
            else
            {
                for (int j = 0; j <= i; j += 1)
                {
                    std::cout << i + 1 << " " << j + 1 << std::endl;
                }
            }

            to_do += 1;
            N -= (1LL << i);
            side ^= 1;
        }
        else
        {
            std::cout << i + 1 << " " << (side ? i + 1 : 1) << std::endl;
        }
    }

    to_do += N;
    for (int i = LIMIT; to_do > 0; i += 1, to_do -= 1)
    {
        std::cout << i + 1 << " " << (side ? i + 1 : 1) << std::endl;
    }
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
        std::cout << "Case #" << test << ":" << std::endl;
        solve_test_case();
    }

    return 0;
}
