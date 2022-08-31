#include <bits/stdc++.h>

int N;
std::vector<int> v;

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> N;
	v.resize(N);
	for (int &i : v)
	{
		std::cin >> i;
	}
	std::vector<int> l(N + 1, 0);
	for (int i = 0; i < N; i += 1)
	{
		l[i + 1] = std::max(l[i], v[i]);
	}
	std::vector<int> r(N + 1, 0);
	for (int i = N - 1; i >= 0; i -= 1)
	{
		r[i] = std::max(r[i + 1], v[i]);
	}
	int ans = 0;
	for (int i = 0; i < N; i += 1)
	{
		if (l[i] > v[i] and r[i] > v[i])
		{
			ans += 1;
		}
	}
	std::cout << ans << std::endl;
	return 0;
}