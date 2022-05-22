#include <iostream>

void solve_test_case()
{
    std::string S;
    std::cin >> S;
    S.push_back('0');

    int qty = 0;
    std::string ans;

    for (const char c : S)
    {
        const int value = c - '0';
        while (qty < value)
        {
            qty += 1;
            ans.push_back('(');
        }
        while (qty > value)
        {
            qty -= 1;
            ans.push_back(')');
        }
        ans.push_back(c);
    }

    ans.pop_back();

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