#include <bits/stdc++.h>

class Solution
{
public:
  Solution()
  {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
  }

  void main()
  {
    std::memset(v, 0, sizeof v);
    std::cin >> N >> K;
    for (int i = 0; i < N; i += 1)
    {
      int l, r;
      std::cin >> l >> r;
      v[l] += 1;
      v[r + 1] -= 1;
      segments.push({{-l, r}, i});
    }
    int current = 0;
    std::vector< int > ans;
    std::priority_queue< std::pair< int, int > > pq;
    for (int i = 0; i < 212345; i += 1)
    {
      while (segments.empty() == false and -segments.top().first.first <= i)
      {
        pq.push({segments.top().first.second, segments.top().second});
        segments.pop();
      }
      current += v[i];
      while (current > K)
      {
        current -= 1;
        ans.push_back(pq.top().second);
        v[pq.top().first + 1] += 1;
        pq.pop();
      }
    }
    std::cout << int(ans.size()) << std::endl;
    for (const int& i : ans)
    {
      std::cout << i + 1 << ' ';
    }
    std::cout << std::endl;
  }

private:
  int N;
  int K;
  int v[212345];
  std::priority_queue< std::pair< std::pair< int, int >, int > > segments;
};

int main()
{
  Solution().main();
  return 0;
}