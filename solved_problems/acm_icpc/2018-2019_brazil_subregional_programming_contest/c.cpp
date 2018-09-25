#include <bits/stdc++.h>
using namespace std;

void update(const auto &idx, auto &bit) {
	for (int i = idx; i < int(bit.size()); i += i & (-i))
		++bit[i];
}

int query(const auto &idx, const auto &bit) {
	int ans = 0;
	for (int i = idx; i > 0; i -= i & (-i))
		ans += bit[i];
	return ans;
}

int main() {
	scanf("%*d %*d");
	vector<int> qtd(2);
	for (int i = 0; i < 2; ++i)
		scanf("%d", &qtd[i]);
	long long int ans = 1LL + (1LL * qtd[0] * qtd[1]);
	for (int i = 0; i < 2; ++i) {
		vector<int> other;
		vector< pair<int, int> > v;
		for (int j = 0; j < qtd[i]; ++j) {
			int x, y; scanf("%d %d", &x, &y);
			v.push_back({-x, y});
			other.push_back(y);
		}
		sort(v.begin(), v.end());
		sort(other.begin(), other.end());
		unordered_map<int, int> convert;
		vector<int> bit(int(v.size()) + 5, 0);
		for (int i = 0, diff = 0; i < int(other.size()); ++i)
			if (!i or other[i] != other[i-1])
				convert[other[i]] = ++diff;
		for (int i = 0; i < int(v.size()); ++i) {
			int idx = convert[v[i].second];
			ans += 1LL + query(idx, bit);
			update(idx, bit); 
		}
	}
	return printf("%lld\n", ans), 0;
}