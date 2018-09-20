#include <bits/stdc++.h>
using namespace std;
const int N = 112345;

class node {
public:
	int lo, hi, value;
	node *left, *right;
	node () {}
	node (const int &_lo, const int &_hi) {
		value = 0;
		lo = _lo, hi = _hi;
		left = right = NULL;
	}
	void update (const int &idx, const int &new_value) {
		if (idx < lo or idx > hi)
			return;
		if (lo == idx and hi == idx) {
			value = new_value;
			return;
		}
		const int mid = (lo + hi) >> 1;
		if (idx <= mid) {
			if (!left)
				left = new node(lo, mid);
			left->update(idx, new_value);
		}
		else {
			if (!right)
				right = new node(mid + 1, hi);
			right->update(idx, new_value);
		}
		value = 0;
		if (left)
			value += left->value;
		if (right)
			value += right->value;
	}
	int query (const int &qlo, const int &qhi) {
		if (lo > qhi or hi < qlo)
			return 0;
		if (lo >= qlo and hi <= qhi)
			return value;
		int ans = 0;
		if (left)
			ans += left->query(qlo, qhi);
		if (right)
			ans += right->query(qlo, qhi);
		return ans;
	}
};

node root[N];
int factor[N], v[N];

void build () {
	for (int i = 0; i < N; ++i)
		factor[i] = i,
		root[i] = node(0, N - 1);
	for (int i = 2; i < N; ++i)
		if (factor[i] == i)
			for (int j = i; j < N; j += i)
				factor[j] = min(factor[j], i);
}

vector<int> factorize (const int &n) {
	set<int> s;
	for (int i = n; i > 1; i /= factor[i])
		s.insert(factor[i]);
	vector<int> ans;
	for (auto i : s)
		ans.push_back(i);
	return ans;
}

void update (const int &idx, const bool &flag) {
	vector<int> current = factorize(v[idx]);
	for (int i = 0; i < (1 << int(current.size())); ++i) {
		int value = 1;
		for (int j = 0; j < int(current.size()); ++j)
			if (i & (1 << j))
				value *= current[j];
		root[value].update(idx, flag);
	}
}

int main () {
	build();
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &v[i]), update(i, true);
	int q; scanf("%d", &q);
	while (q-- > 0) {
		int type; scanf("%d", &type);
		if (type == 1) {
			int i, x; scanf("%d %d", &i, &x), --i;
			update(i, false);
			v[i] = x;
			update(i, true);
		}
		else {
			int x, y, z; scanf("%d %d %d", &x, &y, &z); --x, --y;
			int ans = 0;
			vector<int> current = factorize(z);
			for (int i = 0; i < (1 << int(current.size())); ++i) {
				int value = 1;
				for (int j = 0; j < int(current.size()); ++j)
					if (i & (1 << j))
						value *= current[j];
				if (__builtin_popcount(i) & 1)
					ans -= root[value].query(x, y);
				else
					ans += root[value].query(x, y);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}