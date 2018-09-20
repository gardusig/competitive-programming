#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;

int ans[N];
set<int> milkshake[N][2], customer[N][2], remain;

int main () {
	int c; scanf("%d", &c);
	for (int test = 1; test <= c; ++test) {
		remain.clear();
		int n, m; scanf("%d %d", &n, &m);
		for (int i = 0; i < n; ++i) {
			ans[i] = 0;
			for (int j = 0; j < 2; ++j)
				milkshake[i][j].clear();
		}
		for (int i = 0; i < m; ++i) {
			remain.insert(i);
			for (int j = 0; j < 2; ++j)
				customer[i][j].clear();
		}
		for (int i = 0; i < m; ++i) {
			int qtd; scanf("%d", &qtd);
			while (qtd-- > 0) {
				int x, y; scanf("%d %d", &x, &y); --x;
				customer[i][y].insert(x), milkshake[x][y].insert(i);
			}
		}
		bool flag = true;
		while (remain.size() and flag) {
			int idx = *remain.begin();
			for (auto i : remain)
				if (customer[i][0].size() + customer[i][1].size() < customer[idx][0].size() + customer[idx][1].size())
					idx = i;
			if (customer[idx][0].size() + customer[idx][1].size() == 0)
				flag = false;
			if (customer[idx][0].size() + customer[idx][1].size() == 1) {
				int y = (customer[idx][0].size() ? 0 : 1);
				int x = *customer[idx][y].begin();
				for (auto i : milkshake[x][y])
					remain.erase(i);
				for (auto i : milkshake[x][y ^ 1])
					customer[i][y ^ 1].erase(x);
				milkshake[x][y].clear(), ans[x] = y;
			}
			else
				break;
		}
		if (flag) {
			printf("Case #%d:", test);
			for (int i = 0; i < n; ++i)
				printf(" %d", (ans[i] == 1) ? 1 : 0);
			puts("");
		}
		else
			printf("Case #%d: IMPOSSIBLE\n", test);
	}
	return 0;
}