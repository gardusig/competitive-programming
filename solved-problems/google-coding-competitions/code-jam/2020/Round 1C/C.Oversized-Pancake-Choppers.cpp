#include <iostream>
#include <vector>
#include <algorithm>

void solve_test_case()
{
    int N, D;
    std::cin >> N >> D;

    std::vector<long long int> v(N);
    for (int i = 0; i < N; i += 1)
    {
        std::cin >> v[i];
    }
    std::sort(v.begin(), v.end());

    if (N == 1)
    {
        std::cout << D - N << std::endl;
        return;
    }

    int ans = D - 1;

    for (int i = 0; i < N; i += 1)
    {
        for (int j = i + 1; j < N; j += 1)
        {
            long long int kappa = v[i];
            long long int keepo = v[j];

            if (D == 2)
            {
                if (kappa == keepo)
                {
                    ans = std::min(ans, 0);
                }
            }
            else
            {
                if (kappa + kappa == keepo)
                {
                    ans = std::min(ans, 1);
                }
                if (N == 2)
                {
                    continue;
                }
                for (int k = j + 1; k < N; k += 1)
                {
                    long long int copo = v[k];
                    if (kappa == keepo and kappa == copo)
                    {
                        ans = std::min(ans, 0);
                    }
                    if (kappa == keepo)
                    {
                        ans = std::min(ans, 1);
                    }
                }
            }
        }
    }

    std::cout << ans << std::endl;
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
