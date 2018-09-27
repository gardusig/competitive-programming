#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector<bool> current(m, false);
	int qtd; scanf("%d", &qtd);
	while (qtd-- > 0) {
		int x; scanf("%d", &x), --x;
		current[x] = !current[x];
	}
	vector< vector<int> > v(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &qtd);
		while (qtd-- > 0) {
			int x; scanf("%d", &x), --x;
			v[i].push_back(x);
		}
	}
	for (int i = 0; i < n; ++i)
		v.push_back(v[i]);
	for (int i = 0; i < int(v.size()); ++i) {
		for (auto j : v[i])
			current[j] = !current[j];
		bool flag = true;
		for (auto j : current)
			flag &= !j;
		if (flag)
			return printf("%d\n", i + 1), 0;
	}
	return printf("%d\n", -1), 0;
}