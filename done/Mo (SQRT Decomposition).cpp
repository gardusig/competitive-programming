#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
const int N = 1e6 + 5;

int ans[N], f[N], v[N];
int block_size, current;
vector< pair<ii, int> > mo;

//~ bool cmp (const Query &x, const Query &y) {
	//~ if ((x.l / block_size) == (y.l / block_size))
		//~ return ((x.l / block_size) & 1) ? (x.r < y.r) : (x.r > y.r);
	//~ return (x.l / b) < (y.l / b);
//~ }

bool compare (const pair<ii, int> a, const pair<ii, int> b) {
	if (a.first.first / block_size == b.first.first / block_size)
		return a.first.second < b.first.second;
	return a.first.first < b.first.first;
}

void add (const int x) {
	if (!f[x]++)
		++current;
}

void rem (const int x) {
	if (!--f[x])
		--current;
}

int main () {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &v[i]);
	int q; scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		int x, y; scanf("%d %d", &x, &y);
		mo.push_back(make_pair(make_pair(x, y), i));
	}
	current = 0;
	block_size = sqrt(n) + 1;
	sort(mo.begin(), mo.end(), compare);
	for (int l = 0, r = -1, i = 0; i < q; ++i) {
		int id = mo[i].second;
		int nxt_l = mo[i].first.first;
		int nxt_r = mo[i].first.second;
		for (int j = l; j < nxt_l; ++j)
			rem(v[j]);
		for (int j = nxt_l; j < l; ++j)
			add(v[j]);
		for (int j = nxt_r; j > r; --j)
			add(v[j]);
		for (int j = r; j > nxt_r; --j)
			rem(v[j]);
		l = nxt_l, r = nxt_r, ans[id] = current;
	}
	for (int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}