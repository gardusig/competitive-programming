#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; scanf("%d", &t);
	while (t-- > 0) {
		int n; scanf("%d", &n);
		double ans = 0;
		for (int i = 0; i < n; ++i) {
			int price, quantity, discount; scanf("%d %d %d", &price, &quantity, &discount);
			double previous_price = (1.0 + (discount / 100.0)) * price;
			double new_price = (1.0 - (discount / 100.0)) * previous_price;
			ans += (price - new_price) * quantity;
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}