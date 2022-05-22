#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int N, M, K;
int v[MAXN][MAXN];
int dist[MAXN][MAXN];

int solve()
{
	for (int i = 0; i < N; i += 1)
	{
		for (int j = 0; j < M; j += 1)
		{
			dist[i][j] = INT_MAX;
		}
	}
	priority_queue<pair<int, pair<int, int>>> pq;
	dist[0][0] = 0;
	pq.push({-dist[0][0], {0, 0}});
	while (pq.empty() == false)
	{
		int currentDist = -pq.top().first;
		int i = pq.top().second.first;
		int j = pq.top().second.second;
		pq.pop();
		if (i == N - 1 and j == M - 1)
		{
			return currentDist;
		}
		if (currentDist > dist[i][j])
		{
			continue;
		}
		for (int k = 0; k < 4; k += 1)
		{
			int x = i + dx[k];
			int y = j + dy[k];
			if (x < 0 or x >= N or y < 0 or y >= M)
			{
				continue;
			}
			if (v[i][j] != -1 and v[x][y] != -1 and ((v[i][j] + 1) % K) != v[x][y])
			{
				continue;
			}
			int nxtDist = 0;
			if (v[x][y] != -1)
			{
				int current = currentDist % K;
				if (current < v[x][y])
				{
					nxtDist += v[x][y] - current;
				}
				else
				{
					nxtDist += K - current + v[x][y];
				}
			}
			else
			{
				nxtDist = 1;
			}
			if (currentDist + nxtDist < dist[x][y])
			{
				dist[x][y] = currentDist + nxtDist;
				pq.push({-dist[x][y], {x, y}});
			}
		}
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i += 1)
	{
		for (int j = 0; j < M; j += 1)
		{
			cin >> v[i][j];
		}
	}
	cout << solve() << endl;
	return 0;
}