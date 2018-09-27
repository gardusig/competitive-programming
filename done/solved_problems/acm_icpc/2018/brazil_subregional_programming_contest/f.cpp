#include <bits/stdc++.h>
using namespace std;

class show {
public:
	int start, finish, value, idx;
	show(const int &start, const int &finish, const int &value, const int &idx) {
		this->start = start;
		this->finish = finish;
		this->value = value;
		this->idx = idx;
	}
	bool operator < (const show &other) const {
		return this->start < other.start;
	}
};

int main () {
	vector<show> v;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int qtd; scanf("%d", &qtd);
		while (qtd-- > 0) {
			int start, finish, value; scanf("%d %d %d", &start, &finish, &value);
			v.push_back(show(start, finish, value, i));
		}
	}
	vector<int> nxt;
	sort(v.begin(), v.end());
	for (int i = 0; i < int(v.size()); ++i) {
		nxt.push_back(int(v.size()));
		for (int j = i + 1; j < int(v.size()); ++j)
			if (v[j].start >= v[i].finish)
				nxt[i] = min(nxt[i], j);
	}
	int limit = (1 << n);
	vector< vector<int> > dp(limit + 5);
	for (int i = 0; i < limit; ++i)
		dp[i] = vector<int>(int(v.size()) + 5, INT_MIN);
	for (int j = 0; j < int(v.size()); ++j)
		dp[0][j] = 0;
	for (int i = 0; i < limit; ++i)
		for (int j = 0; j < int(v.size()); ++j) {
			dp[i | (1 << v[j].idx)][nxt[j]] = max(dp[i | (1 << v[j].idx)][nxt[j]], dp[i][j] + v[j].value);
			dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
		}
	int ans = dp[limit - 1][int(v.size())];
	if (ans <= 0)
		ans = -1;
	return printf("%d\n", ans), 0;
}