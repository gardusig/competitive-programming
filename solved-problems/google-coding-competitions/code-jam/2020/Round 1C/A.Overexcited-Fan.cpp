#include <iostream>

void solve_test_case()
{
    int x, y;
    std::string s;
    std::cin >> x >> y >> s;

    int ans = 0;

    for (const char c : s)
    {
        if (std::abs(x) + std::abs(y) <= ans)
        {
            std::cout << ans << std::endl;
            return;
        }

        ans += 1;

        if (c == 'N')
        {
            y += 1;
        }
        if (c == 'S')
        {
            y -= 1;
        }
        if (c == 'E')
        {
            x += 1;
        }
        if (c == 'W')
        {
            x -= 1;
        }
    }

    if (std::abs(x) + std::abs(y) <= ans)
    {
        std::cout << ans << std::endl;
        return;
    }

    std::cout << "IMPOSSIBLE" << std::endl;
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
        std::cout << "Case #" << test << ": ";
        solve_test_case();
    }

    return 0;
}
