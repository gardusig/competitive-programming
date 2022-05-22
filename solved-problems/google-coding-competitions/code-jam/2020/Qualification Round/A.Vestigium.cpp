#include <iostream>
#include <vector>
#include <set>

void solve_test_case()
{
    int N;
    std::vector<std::vector<int>> M;

    std::cin >> N;
    M.resize(N);
    for (int i = 0; i < N; i += 1)
    {
        M[i].resize(N);
        for (int &j : M[i])
        {
            std::cin >> j;
        }
    }

    int trace = 0;

    std::set<int> qty_rows;
    std::set<int> qty_columns;

    std::vector<std::set<int>> rows(N);
    std::vector<std::set<int>> columns(N);

    for (int i = 0; i < N; i += 1)
    {
        for (int j = 0; j < N; j += 1)
        {
            const int value = M[i][j];

            if (i == j)
            {
                trace += value;
            }

            if (rows[i].count(value))
            {
                qty_rows.insert(i);
            }
            rows[i].insert(value);

            if (columns[j].count(value))
            {
                qty_columns.insert(j);
            }
            columns[j].insert(value);
        }
    }

    std::cout << trace << ' ' << qty_rows.size() << ' ' << qty_columns.size() << std::endl;
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