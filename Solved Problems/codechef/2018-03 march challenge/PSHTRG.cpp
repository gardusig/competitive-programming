#include <bits/stdc++.h>
using namespace std;
const int N = 112345;
typedef long long int ll;

int fib[N];
int qtd = N, n, q;

void build () {
	fib[0] = 1;
	fib[1] = 1;
	fib[2] = 2;
	for (int i = 3; i < N; ++i) {
		fib[i] = fib[i-1] + fib[i-2];
		if (fib[i] > 1123456789) {
			qtd = i + 5;
			return;
		}
	}
}

class node {
public:
	int lo, hi;
	vector<int> value;
	node *left, *right;
	node () {}
	node (const int &_lo, const int &_hi) {
		value.clear();
		lo = _lo, hi = _hi;
		left = right = NULL;
		if (lo == hi)
			return;
		const int mid = (lo + hi) >> 1;
		left = new node(lo, mid);
		right = new node(mid + 1, hi);
	}
	vector<int> merge (const vector<int> &a, const vector<int> &b) {
		vector<int> ans;
		for (int i = 0, j = 0; int(ans.size()) < qtd;) {
			if (i < int(a.size()) and j < int(b.size())) {
				if (a[i] > b[j])
					ans.push_back(a[i++]);
				else
					ans.push_back(b[j++]);
			}
			else if (i < int(a.size()))
				ans.push_back(a[i++]);
			else if (j < int(b.size()))
				ans.push_back(b[j++]);
			else
				break;
		}
		return ans;
	}
	void update (const int &idx, const int &new_value) {
		if (idx < lo or idx > hi)
			return;
		if (lo == idx and hi == idx) {
			value.clear();
			value.push_back(new_value);
			return;
		}
		left->update(idx, new_value);
		right->update(idx, new_value);
		value = merge(left->value, right->value);
	}
	vector<int> query (const int &qlo, const int &qhi) {
		if (lo > qhi or hi < qlo)
			return vector<int>();
		if (lo >= qlo and hi <= qhi)
			return value;
		vector<int> a = left->query(qlo, qhi);
		vector<int> b = right->query(qlo, qhi);
		return merge(a, b);
	}
};

int main () {
	build();
	scanf("%d %d", &n, &q);
	node root = node(0, n-1);
	for (int i = 0; i < n; ++i) {
		int x; scanf("%d", &x);
		root.update(i, x);
	}
	while (q-- > 0) {
		int type; scanf("%d", &type);
		if (type == 1) {
			int idx, new_value; scanf("%d %d", &idx, &new_value), --idx;
			root.update(idx, new_value);
		}
		else {
			int x, y; scanf("%d %d", &x, &y); --x, --y;
			vector<int> ans = root.query(x, y);
			ll best = 0;
			for (int i = 0; i < int(ans.size()) - 2; ++i)
				if (ans[i] < ans[i+1] + ans[i+2])
					best = max(best, ll(ans[i]) + ans[i+1] + ans[i+2]);
			printf("%lld\n", best);
		}
	}
	return 0;
}