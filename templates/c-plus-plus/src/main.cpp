#include <iostream>
#include <memory>

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    std::unique_ptr<int> ptr(new int(1));

    return 0;
}
