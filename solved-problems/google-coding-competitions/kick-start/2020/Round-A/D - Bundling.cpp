#include <iostream>
#include <map>
#include <memory>

class Node
{
public:
    void add(const std::string &s, const int i)
    {
        if (i == int(s.size()))
        {
            this->qty += 1;
            return;
        }

        const char j = s[i];

        if (!this->nxt.count(j))
        {
            this->nxt[j] = std::make_unique<Node>();
        }

        this->nxt[j]->add(s, i + 1);
    }

    std::pair<long long int, int> dfs(const int h, const int K)
    {
        long long int ans = 0;
        int current_size = this->qty;

        for (const auto &j : this->nxt)
        {
            const auto kappaloiro = j.second->dfs(h + 1, K);
            ans += kappaloiro.first;
            current_size += kappaloiro.second;
        }

        ans += (1LL * h * (current_size / K));
        return {ans, current_size % K};
    }

private:
    int qty = 0;
    std::map<char, std::unique_ptr<Node>> nxt;
};

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;

    for (int test = 1; test <= T; test += 1)
    {
        int N, K;
        std::cin >> N >> K;

        std::unique_ptr<Node> trie(new Node());

        for (int i = 0; i < N; i += 1)
        {
            std::string s;
            std::cin >> s;
            trie->add(s, 0);
        }

        std::cout << "Case #" << test << ": " << trie->dfs(0, K).first << std::endl;
    }

    return 0;
}