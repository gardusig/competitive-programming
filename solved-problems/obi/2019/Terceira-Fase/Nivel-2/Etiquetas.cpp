#include <bits/stdc++.h>

const int MAX_SIZE = 11234;

int N, K, C;
int v[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];
int sum[MAX_SIZE];

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> N >> K >> C;
	int total = 0;
	sum[0] = 0;
	for (int i = 0; i < N; i += 1)
	{
		std::cin >> v[i];
		total += v[i];
		sum[i + 1] = sum[i] + v[i];
	}
	for (int i = 0; i <= N; i += 1)
	{
		for (int j = 0; j <= K; j += 1)
		{
			dp[i][j] = !j ? 0 : 1e8 + 5;
		}
	}
	for (int i = 0; i < N; i += 1)
	{
		for (int j = 0; j <= K; j += 1)
		{
			dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j]);
			if (j < K and i + C <= N)
			{
				dp[i + C][j + 1] = std::min(dp[i + C][j + 1], sum[i + C] - sum[i] + dp[i][j]);
			}
		}
	}
	std::cout << total - dp[N][K] << std::endl;
	return 0;
}