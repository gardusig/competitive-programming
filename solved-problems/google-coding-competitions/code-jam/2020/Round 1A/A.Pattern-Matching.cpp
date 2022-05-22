#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool valid(const std::string &a, const std::string &b)
{
    if (a.empty())
    {
        return true;
    }

    if (a.length() < b.length() and b.substr(0, a.length()) != a)
    {
        return false;
    }

    if (a.length() >= b.length() and a.substr(0, b.length()) != b)
    {
        return false;
    }

    return true;
}

void solve_test_case()
{
    int N;
    std::cin >> N;
    std::vector<std::string> v;

    for (int i = 0; i < N; i += 1)
    {
        std::string s;
        std::cin >> s;
        v.push_back(s);
    }

    std::string prefix;
    std::string suffix;

    for (const std::string &s : v)
    {
        std::string p;
        for (const char &c : s)
        {
            if (c == '*')
            {
                break;
            }
            p.push_back(c);
        }

        if (not valid(prefix, p))
        {
            std::cout << "*" << std::endl;
            return;
        }

        if (p.length() > prefix.length())
        {
            prefix = p;
        }

        std::string suf;
        std::string rev = s;
        std::reverse(rev.begin(), rev.end());
        for (const char &c : rev)
        {
            if (c == '*')
            {
                break;
            }
            suf.push_back(c);
        }

        if (not valid(suffix, suf))
        {
            std::cout << "*" << std::endl;
            return;
        }

        if (suf.length() > suffix.length())
        {
            suffix = suf;
        }
    }

    std::string ans = "";
    ans += prefix;
    for (const std::string &s : v)
    {
        for (const char &c : s)
        {
            if (c == '*')
            {
                continue;
            }
            ans.push_back(c);
        }
    }
    std::reverse(suffix.begin(), suffix.end());
    ans += suffix;



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