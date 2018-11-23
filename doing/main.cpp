#include <bits/stdc++.h>
using namespace std;

void optimize_in_out() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0);
	cout.tie(0);
}

int main () {
	optimize_in_out();
	int N, M; cin >> N >> M;
	vector< pair< pair<int, int>, int > > v;
	int sum = 0;
	for (int i = 0; i < M; ++i) {
		int A, B; cin >> A >> B;
		v.push_back({{A, B}, i});
		sum += B;
	}
	if (sum != N - 1)
		return cout << -1 << '\n', 0;
	sort(v.begin(), v.end(), compare);
	bool flag = false;
	for (int i = int(v.size()) - 1; i >= 0; --i) {
		if (flag == true and v[i].first.second == 0)
			return cout << -1 << '\n', 0;
		if (v[i].first.second == 1)
			flag = true;
	}
	int trash_idx = 0, current = 0;
	vector<int> trash(N);
	for (int i = 0; i < N; ++i)
		trash[i] = i + 2;
	vector< pair<int, int> > ans(M);
	for (const auto &i: v) {
		if (i.first.second == 1) {
			ans[i.second] = {current, current + 1};
			current += 1;
		}
		else {
			ans[i.second] = {trash_idx, trash[trash_idx]};
			if (trash[trash_idx] + 1 == N)
				trash_idx += 1;
			else
				trash[trash_idx] += 1;
		}
	}
	for (const auto &i: ans)
		cout << i.first + 1 << ' ' << i.second + 1 << '\n';
	return 0;
}