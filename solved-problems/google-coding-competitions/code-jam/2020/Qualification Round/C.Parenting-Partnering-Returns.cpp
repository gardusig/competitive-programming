#include <iostream>
#include <vector>
#include <algorithm>

void solve_test_case()
{
    int N;
    std::cin >> N;
    std::vector<std::pair<std::pair<int, int>, int>> v(N);

    for (int i = 0; i < N; i += 1)
    {
        std::cin >> v[i].first.first >> v[i].first.second;
        v[i].second = i;
    }

    std::sort(v.begin(), v.end());

    std::vector<int> pos(2, 0);
    std::vector<int> ans(N);

    for (const auto &i : v)
    {
        const int L = i.first.first;
        const int R = i.first.second;
        const int idx = i.second;

        bool found = false;

        for (int j = 0; j < 2; j += 1)
        {
            if (pos[j] <= L)
            {
                found = true;
                pos[j] = R;
                ans[idx] = j;
                break;
            }
        }

        if (not found)
        {
            std::cout << "IMPOSSIBLE" << std::endl;
            return;
        }
    }

    for (const int i : ans)
    {
        std::cout << (i ? 'J' : 'C');
    }
    std::cout << std::endl;
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