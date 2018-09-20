#include <bits/stdc++.h>
using namespace std;
const int N = 3;

int n;

bool solve (const string a, const string s, const string b) {
	char less = '$', greater = '$';
	for (int i = 0; i < n; ++i)
		if (a[i] != s[i]) {
			less = a[i];
			greater = s[i];
			break;
		}
	for (int i = 0; i < n; ++i)
		if (s[i] != b[i])
			return !(s[i] == greater and b[i] == less);
	return false;
}

int main () {
	int t; scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		string v[N];
		scanf("%d", &n);
		for (int i = 0; i < N; ++i)
			cin >> v[i];
		printf("Case #%d:", test);
		for (int i = 0; i < N; ++i) {
			bool kappa = solve(v[(i - 1 + N) % N], v[i], v[(i + 1) % N]);
			bool keepo = solve(v[(i + 1) % N], v[i], v[(i - 1 + N) % N]);
			printf(" %s", (kappa | keepo) ? "YES" : "NO");
		}
		puts("");
	}
	return 0;
}