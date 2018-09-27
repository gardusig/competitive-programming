#include <bits/stdc++.h>
using namespace std;
const int N = 112345;
typedef long long int ll;

int v[N];
ll sum[N];
queue<int> add, rem;
vector<int> start, finish;

int main () {
	int t; scanf("%d", &t);
	while (t-- > 0) {
		int n; scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &v[i]);
		sum[0] = v[0];
		for (int i = 1; i < n; ++i)
			sum[i] = sum[i-1] + v[i];
		start.clear(), finish.clear();
		for (int i = 0; i < n; ++i) {
			int lo = 0, hi = i - 1;
			while (lo <= hi) {
				const int mid = (lo + hi) >> 1;
				ll current = sum[i - 1] - sum[mid];
				if (v[i] < current)
					lo = mid + 1;
				else
					hi = mid - 1;
			}
			if (lo < i)
				start.push_back(lo),
				finish.push_back(i - 1);
		}
		for (int i = 0; i < n; ++i) {
			int lo = i + 1, hi = n - 1;
			while (lo <= hi) {
				const int mid = (lo + hi) >> 1;
				ll current = sum[mid - 1] - sum[i];
				if (v[i] < current)
					hi = mid - 1;
				else
					lo = mid + 1;
			}
			if (hi > i)
				start.push_back(i + 1),
				finish.push_back(hi);
		}
		int current = 0;
		sort(start.begin(), start.end());
		sort(finish.begin(), finish.end());
		for (auto i : start)
			add.push(i);
		for (auto i : finish)
			rem.push(i);
		for (int i = 0; i < n; ++i) {
			while (add.size() and i >= add.front())
				++current, add.pop();
			while (rem.size() and i > rem.front())
				--current, rem.pop();
			printf("%d%c", current, (i == n-1) ? '\n' : ' ');
			while (rem.size() and i >= rem.front())
				--current, rem.pop();
		}
	}
	return 0;
}