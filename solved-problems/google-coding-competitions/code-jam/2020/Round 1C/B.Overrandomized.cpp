#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

void solve_test_case()
{
    int U;
    std::cin >> U;

    std::set<char> letters;
    std::set<char> invalid_zero;
    std::map<char, int> frequency;

    for (int i = 0; i < 1e4; i += 1)
    {
        long long int N;
        std::string s;
        std::cin >> N >> s;

        invalid_zero.insert(s[0]);
        frequency[s[0]] += 1;
        for (const char c : s)
        {
            letters.insert(c);
        }
    }

    std::string ans = "";

    for (const char letter : letters)
    {
        if (not invalid_zero.count(letter))
        {
            frequency.erase(letter);
            ans.push_back(letter);
        }
    }

    std::vector<std::pair<int, char>> v;
    for (const auto i : frequency)
    {
        v.push_back({i.second, i.first});
    }
    std::sort(v.rbegin(), v.rend());

    for (const auto i : v)
    {
        ans.push_back(i.second);
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
