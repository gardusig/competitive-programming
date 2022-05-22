#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <climits>

const int CORRECT = 200;
const int ERROR = 404;
const int BORDER = 1000000000;
const int LIMIT_QUERIES = 300;
const int UNDEFINED = INT_MAX;

int A, B;
int queries;

std::string query(const int x, const int y)
{
    queries += 1;
    assert(queries <= LIMIT_QUERIES);

    std::cout << x << " " << y << "\n"
              << std::flush;

    std::string response;
    std::cin >> response;
    assert(response != "WRONG");

    if (response == "CENTER")
    {
        throw CORRECT;
    }

    return response;
}

std::pair<int, int> get_first_inside_point()
{
    std::vector<std::pair<int, int>> v;

    v.push_back({+(BORDER >> 1), 0});
    v.push_back({+(BORDER >> 1), +(BORDER >> 1)});
    v.push_back({+(BORDER >> 1), -(BORDER >> 1)});

    v.push_back({0, 0});
    v.push_back({0, +(BORDER >> 1)});
    v.push_back({0, -(BORDER >> 1)});

    v.push_back({-(BORDER >> 1), 0});
    v.push_back({-(BORDER >> 1), +(BORDER >> 1)});
    v.push_back({-(BORDER >> 1), -(BORDER >> 1)});

    for (const auto i : v)
    {
        const std::string response = query(i.first, i.second);

        if (response == "MISS")
        {
            continue;
        }

        if (response == "HIT")
        {
            return i;
        }
    }

    assert(false);
}

void solve_test_case()
{
    queries = 0;

    auto start = get_first_inside_point();

    int lo, hi, ans;

    ans = INT_MAX;
    lo = -BORDER;
    hi = start.first;
    while (lo <= hi)
    {
        const int mid = lo + ((hi - lo) >> 1);

        const std::string response = query(mid, start.second);

        if (response == "MISS")
        {
            lo = mid + 1;
        }
        else
        {
            ans = mid;
            hi = mid - 1;
        }
    }
    assert(ans != INT_MAX);
    const int LEFT = ans;

    ans = INT_MAX;
    lo = start.first;
    hi = +BORDER;
    while (lo <= hi)
    {
        const int mid = lo + ((hi - lo) >> 1);

        const std::string response = query(mid, start.second);

        if (response == "MISS")
        {
            hi = mid - 1;
        }
        else
        {
            ans = mid;
            lo = mid + 1;
        }
    }
    assert(ans != INT_MAX);
    const int RIGHT = ans;

    ans = INT_MAX;
    lo = -BORDER;
    hi = start.second;
    while (lo <= hi)
    {
        const int mid = lo + ((hi - lo) >> 1);

        const std::string response = query(start.first, mid);

        if (response == "MISS")
        {
            lo = mid + 1;
        }
        else
        {
            ans = mid;
            hi = mid - 1;
        }
    }
    assert(ans != INT_MAX);
    const int DOWN = ans;

    ans = INT_MAX;
    lo = start.second;
    hi = +BORDER;
    while (lo <= hi)
    {
        const int mid = lo + ((hi - lo) >> 1);

        const std::string response = query(start.first, mid);

        if (response == "MISS")
        {
            hi = mid - 1;
        }
        else
        {
            ans = mid;
            lo = mid + 1;
        }
    }
    assert(ans != INT_MAX);
    const int UP = ans;

    int x = (RIGHT + LEFT) >> 1;
    int y = (UP + DOWN) >> 1;

    query(x, y);

    throw ERROR;
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T >> A >> B;

    for (int test = 1; test <= T; test += 1)
    {
        try
        {
            solve_test_case();
        }
        catch (const int value)
        {
            if (value == CORRECT)
            {
                continue;
            }

            assert(false);
        }
    }

    return 0;
}
