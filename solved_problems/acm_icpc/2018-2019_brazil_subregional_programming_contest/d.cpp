#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; scanf("%d", &n);
	int ans = 0;
	while (n-- > 0) {
		int x; scanf("%d", &x);
		ans += (x > 1);
	}
	return printf("%d\n", ans), 0;
}