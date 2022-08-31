#include <bits/stdc++.h>

class FenwickTree
{
public:
    FenwickTree(const int size)
    {
        this->v = std::vector<int>(size, 0);
    }

    void update(const int idx, const int value)
    {
        for (int i = idx; i < int(v.size()); i += i & (-i))
        {
            v[i] += value;
        }
    }

    int query(const int idx)
    {
        int ans = 0;
        for (int i = idx; i > 0; i -= i & (-i))
        {
            ans += v[i];
        }
        return ans;
    }

private:
    std::vector<int> v;
};

int N, M;
std::vector<std::pair<int, std::pair<int, int>>> v;
std::vector<std::vector<std::pair<int, int>>> g;
std::set<int> unvisited;
FenwickTree *bit = nullptr;

bool dfs(const int i)
{
    bit->update(i + 1, +1);

    std::vector<int> nxt;
    for (const std::pair<int, int> &j : g[i])
    {
        const int l = j.first;
        const int r = j.second;

        if (bit->query(r + 1) - bit->query(l))
        {
            return true;
        }

        std::vector<int> to_remove;
        for (auto it = unvisited.lower_bound(l); it != unvisited.end() and *it <= r; ++it)
        {
            to_remove.push_back(*it);
        }
        for (const int &j : to_remove)
        {
            nxt.push_back(j);
            unvisited.erase(j);
        }
    }

    for (const int &j : nxt)
    {
        if (dfs(j))
        {
            return true;
        }
    }

    bit->update(i + 1, -1);
    return false;
}

int main()
{
    std::ios_base::sync_with_stdio();
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N >> M;
    for (int i = 0; i < M; i += 1)
    {
        int U, L, R;
        std::cin >> U >> L >> R;
        U -= 1;
        L -= 1;
        R -= 1;
        v.push_back({U, {L, R}});
    }

    int ans = -1;
    int lo = 1;
    int hi = M;
    g.resize(N);

    while (lo <= hi)
    {
        const int mid = lo + ((hi - lo) >> 1);
        g.clear();
        g.resize(N);
        for (int i = 0; i < mid; i += 1)
        {
            g[v[i].first].push_back(v[i].second);
        }

        unvisited.clear();
        for (int i = 0; i < N; i += 1)
        {
            unvisited.insert(i);
        }

        bool valid = false;
        bit = new FenwickTree(N + 1);

        while (!unvisited.empty() and !valid)
        {
            const int source = *unvisited.begin();
            unvisited.erase(unvisited.begin());
            valid |= dfs(source);
        }

        if (valid)
        {
            ans = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
