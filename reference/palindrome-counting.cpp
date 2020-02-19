#include <bits/stdc++.h>
 
std::vector<int> v;
 
long long int query(const long long int x)
{
	if (x == 0)
	{
		return 0;
	}
 
	v.clear();
	for (long long int i = x; i > 0; i /= 10)
	{
		v.push_back(i % 10);
	}
	std::reverse(v.begin(), v.end());
 
	long long int ans = 0;
	const int size = (int(v.size()) + 1) >> 1;
 
	long long int pot = 1;
	for (int i = 1; i < size; i += 1, pot *= 10)
	{
		ans += ((9LL * pot) << 1);
	}
 
	if (!(int(v.size()) & 1))
	{
		ans += (9LL * pot);
	}
 
	ans += 1LL * (v[0] - 1) * pot;
	pot /= 10;
 
	for (int i = 1; i < size; i += 1, pot /= 10)
	{
		ans += 1LL * v[i] * pot;
	}
 
	bool valid = true;
	for (int i = (int(v.size()) >> 1) - 1; i >= 0; i -= 1)
	{
		if (v[int(v.size()) - i - 1] == v[i])
		{
			continue;
		}
		if (v[int(v.size()) - i - 1] < v[i])
		{
			valid = false;
		}	
		break;
	}
 
	ans += valid;
 
	return ans;
}
 
int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
 
	int T;
	std::cin >> T;
 
	while (T--> 0)
	{
		int X, K;
		std::cin >> X >> K;
 
		const long long int before = query(X - 1);
 
		long long int lo = X;
		long long int hi = LLONG_MAX;
 
		while (lo <= hi)
		{
			const long long int mid = lo + ((hi - lo) >> 1);
 
			const long long int current = query(mid);
 
			if (current - before < K)
			{
				lo = mid + 1;
			}
			else
			{
				hi = mid - 1;
			}
		}
 
		assert(hi + 1 > 0);
 
		std::cout << hi + 1 << std::endl;
	}
 
	return 0;
}
