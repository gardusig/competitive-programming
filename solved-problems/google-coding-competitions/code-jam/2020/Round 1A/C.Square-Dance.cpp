#include <iostream>
#include <vector>
#include <queue>
#include <set>

std::vector<std::pair<int, int>> get_edges(const int i, const int j, const std::vector<std::set<int>> &rows, const std::vector<std::set<int>> &columns)
{
    std::vector<std::pair<int, int>> v;

    auto up = columns[j].lower_bound(i);
    if (up != columns[j].begin())
    {
        --up;
        v.push_back({*up, j});
    }

    auto down = columns[j].upper_bound(i);
    if (down != columns[j].end())
    {
        v.push_back({*down, j});
    }

    auto left = rows[i].lower_bound(j);
    if (left != rows[i].begin())
    {
        --left;
        v.push_back({i, *left});
    }

    auto right = rows[i].upper_bound(j);
    if (right != rows[i].end())
    {
        v.push_back({i, *right});
    }

    return v;
}

void solve_test_case()
{
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> v(N);

    long long int total = 0;

    for (int i = 0; i < N; i += 1)
    {
        v[i].resize(M);

        for (int j = 0; j < M; j += 1)
        {
            std::cin >> v[i][j];
            total += v[i][j];
        }
    }

    std::vector<std::set<int>> rows(N);
    for (int i = 0; i < N; i += 1)
    {
        for (int j = 0; j < M; j += 1)
        {
            rows[i].insert(j);
        }
    }

    std::vector<std::set<int>> columns(M);
    for (int j = 0; j < M; j += 1)
    {
        for (int i = 0; i < N; i += 1)
        {
            columns[j].insert(i);
        }
    }

    long long int ans = 0;

    std::set<std::pair<int, int>> nxt;
    for (int i = 0; i < N; i += 1)
    {
        for (int j = 0; j < M; j += 1)
        {
            nxt.insert({i, j});
        }
    }

    while (true)
    {
        ans += total;

        std::vector<std::pair<int, int>> q;

        while (not nxt.empty())
        {
            const int i = nxt.begin()->first;
            const int j = nxt.begin()->second;
            nxt.erase(nxt.begin());

            int sum = 0;
            int qty = 0;

            for (const auto &k : get_edges(i, j, rows, columns))
            {
                qty += 1;
                sum += v[k.first][k.second];
            }

            if (qty == 0 or 1LL * qty * v[i][j] >= sum)
            {
                continue;
            }

            q.push_back({i, j});
        }

        if (q.empty())
        {
            break;
        }

        for (const auto &remove : q)
        {
            const int i = remove.first;
            const int j = remove.second;

            total -= v[i][j];

            rows[i].erase(j);
            columns[j].erase(i);
        }

        for (const auto &remove : q)
        {
            const int i = remove.first;
            const int j = remove.second;

            for (const auto &k : get_edges(i, j, rows, columns))
            {
                nxt.insert(k);
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