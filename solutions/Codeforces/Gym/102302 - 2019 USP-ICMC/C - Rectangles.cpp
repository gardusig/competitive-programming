// <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

// </template>

const int MAX_SIZE = 4123;

class Solution {
private:
	int N;
	vector< int > X[MAX_SIZE];
	vector< int > Y[MAX_SIZE];
	int sum[MAX_SIZE][MAX_SIZE];
	vector< pair< int, int > > v;

	void build() {
		int size = 0;
		set< int > s;
		unordered_map< int, int > convert;
		for (const auto &i: v) {
			s.insert(i.first);
			s.insert(i.second);
		}
		for (const int &i: s) {
			size += 1;
			convert[i] = size;
		}
		for (const auto &i: v) {
			const int x = convert[i.first];
			const int y = convert[i.second];
			X[x].push_back(y);
			Y[y].push_back(x);
			sum[x][y] = 1;
		}
		for (int i = 0; i < MAX_SIZE; i += 1) {
			sort(X[i].begin(), X[i].end());
		}
		for (int i = 0; i < MAX_SIZE; i += 1) {
			sort(Y[i].begin(), Y[i].end());
		}
		for (int i = 0; i < MAX_SIZE; i += 1) {
			for (int j = 0; j < MAX_SIZE; j += 1) {
				if (i > 0) {
					sum[i][j] += sum[i - 1][j];
				}
				if (j > 0) {
					sum[i][j] += sum[i][j - 1];
				}
				if (i > 0 and j > 0) {
					sum[i][j] -= sum[i - 1][j - 1];
				}
			}
		}
	}

	int query(const int &x_min, const int &y_min, const int &x_max, const int &y_max) {
		int ans = sum[x_max][y_max];
		ans -= sum[x_min - 1][y_max];
		ans -= sum[x_max][y_min - 1];
		ans += sum[x_min - 1][y_min - 1];
		return ans;
	}

	int solve() {
		int ans = 0;
		for (int x_min = 0; x_min < MAX_SIZE; x_min += 1) {
			for (int i = 1; i < int(X[x_min].size()); i += 1) {
				const int &y_min = X[x_min][i - 1];
				const int &y_max = X[x_min][i];
				const auto &kappa = upper_bound(Y[y_min].begin(), Y[y_min].end(), x_min);
				const auto &keepo = upper_bound(Y[y_max].begin(), Y[y_max].end(), x_min);
				if (kappa == Y[y_min].end() or keepo == Y[y_max].end() or *kappa != *keepo) {
					continue;
				}
				const int &x_max = *kappa;
				if (query(x_min, y_min, x_max, y_max) == 4) {
					ans += 1;
				}
			}
		}
		return ans;
	}

public:
	Solution() {
		ios_base::sync_with_stdio(0);
		cin.tie(0);
		cout.tie(0);
		cin >> N;
		for (int i = 0; i < N; i += 1) {
			int x, y;
			cin >> x >> y;
			v.push_back({x, y});
		}
		build();
		cout << solve() << endl;
	}
};

int main() {
	Solution();
	return 0;
}