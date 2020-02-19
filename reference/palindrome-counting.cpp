#include <bits/stdc++.h>
 
int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
 
	int N;
	std::cin >> N;
 
	std::vector<int> v(N);
	for (int &i : v)
	{
		std::cin >> i;
	}
 
	std::vector<double> kappa(N);
	for (int i = N - 1; i >= 0; i -= 1)
	{
		kappa[i] = std::sin(v[i]) * std::cos(v[i]);
		if (i < N - 1)
		{
			kappa[i] += kappa[i + 1];
		}
	}
 
	std::vector<double> keepo(N);
	for (int i = N - 1; i >= 0; i -= 1)
	{
		keepo[i] = std::sin(v[i]) * std::sin(v[i]) + std::cos(v[i]) * std::cos(v[i]);
		if (i < N - 1)
		{
			keepo[i] += keepo[i + 1];
		}
	}
 
	double ans = 0;
 
	for (int i = 0; i < N - 1; i += 1)
	{
		ans += (std::sin(v[i]) * std::sin(v[i]) + std::cos(v[i]) * std::cos(v[i])) * kappa[i + 1];
		ans += (std::sin(v[i]) * std::cos(v[i]) * keepo[i + 1]);
	}
 
	std::cout << std::fixed << std::setprecision(2) << ans << std::endl;
 
	return 0;
}
