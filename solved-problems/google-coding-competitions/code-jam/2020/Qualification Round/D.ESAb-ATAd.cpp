#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <memory>
#include <algorithm>

class Middleware
{
public:
    Middleware() : m_queries(0), mc_LIMIT(150) {}

    char send(const int pos)
    {
        this->add();
        std::cout << pos + 1 << std::endl << std::flush;
        return this->receive();
    }

    char send(const std::vector<char> &v) const
    {
        for (const char i : v)
        {
            std::cout << i;
        }
        std::cout << std::endl << std::flush;
        return this->receive();
    }

private:
    const int mc_LIMIT;

    int m_queries;

    void add()
    {
        this->m_queries += 1;
        assert(this->m_queries <= mc_LIMIT);
    }

    char receive() const
    {
        char response;
        std::cin >> response;
        assert(response != 'N');
        return response;
    }
};

std::vector<char> get_reverse(const std::vector<char> &v)
{
    std::vector<char> ret = v;
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::vector<char> get_complement(const std::vector<char> &v)
{
    std::vector<char> ret = v;
    for (char &i : ret)
    {
        if (i != -1)
        {
            i ^= 1;
        }
    }
    return ret;
}

void solve_test_case(const int B)
{
    std::unique_ptr<Middleware> middleware(new Middleware());

    std::vector<char> ans(B, -1);

    while (true)
    {
        if (*std::min_element(ans.begin(), ans.end()) != -1)
        {
            break;
        }

        std::set<std::vector<char>> possible;
        possible.insert(ans);
        possible.insert(get_reverse(ans));
        possible.insert(get_complement(ans));
        possible.insert(get_reverse(get_complement(ans)));

        int available_queries = 10;

        for (int i = 0; i < B and available_queries > 0 and int(possible.size()) > 1; i += 1)
        {
            std::set<char> values;

            for (const auto &v : possible)
            {
                if (v[i] == -1)
                {
                    continue;
                }
                values.insert(v[i]);
            }

            if (int(values.size()) < 2)
            {
                continue;
            }

            available_queries -= 1;
            const char response = middleware->send(i);

            std::vector<std::vector<char>> to_remove;
            for (const auto &v : possible)
            {
                if (v[i] != -1 and v[i] != response)
                {
                    to_remove.push_back(v);
                }
            }
            for (const auto &v : to_remove)
            {
                possible.erase(v);
            }
        }

        std::set<int> ask;
        for (int i = 0; i < B; i += 1)
        {
            std::set<char> values;
            for (const auto &v : possible)
            {
                values.insert(v[i]);
            }
            if (int(values.size()) > 1 or *values.begin() == -1)
            {
                ask.insert(i);
                ans[i] = -1;
            }
            else
            {
                ans[i] = *values.begin();
            }
        }

        int nxt = -1;
        while (not ask.empty() and available_queries)
        {
            available_queries -= 1;
            const int pos = (nxt != -1) ? nxt : *ask.begin();
            const char response = middleware->send(pos);
            ans[pos] = response;
            ask.erase(pos);

            nxt = B - pos - 1;
            if (not ask.count(nxt))
            {
                nxt = -1;
            }
        }
    }

    middleware->send(ans);
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int T, B;
    std::cin >> T >> B;
    for (int test = 1; test <= T; test += 1)
    {
        solve_test_case(B);
    }

    return 0;
}