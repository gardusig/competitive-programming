#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int ans[1005];
vector<pair<int, int>> vizinhos[1005];

void bfs(int v)
{
	priority_queue<pii, vector<pii>, greater<pii>> fila;
	ans[v] = 0;
	fila.push(pii(ans[v], v));
	while (fila.empty() == false)
	{
		int current_dist = fila.top().first;
		int vertex = fila.top().second;
		fila.pop();
		if (current_dist != ans[vertex])
		{
			continue;
		}
		for (int i = 0; i < int(vizinhos[vertex].size()); i += 1)
		{
			int nxt_dist = current_dist + vizinhos[vertex][i].second;
			int nxt_vertex = vizinhos[vertex][i].first;
			if (nxt_dist < ans[nxt_vertex])
			{
				ans[nxt_vertex] = nxt_dist;
				fila.push({ans[nxt_vertex], nxt_vertex});
			}
		}
	}
}

int main()
{
	int p, pont;
	cin >> p >> pont;
	for (int i = 0; i < pont; i++)
	{
		int S, T, P;
		cin >> S >> T >> P;
		vizinhos[T].push_back(pii(S, P));
		vizinhos[S].push_back(pii(T, P));
	}
	for (int i = 0; i < 1005; i++)
		ans[i] = 999999999;
	bfs(0);
	cout << ans[p + 1] << endl;
}