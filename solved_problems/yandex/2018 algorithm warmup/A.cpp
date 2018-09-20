#include <bits/stdc++.h>
using namespace std;

int main () {
	int x, y; scanf("%d %d", &x, &y);
	if (x != 0 and x != 6)
		x = 12 - x;
	if (y != 0 and y != 30)
		y = 60 - y;
	return !printf("%d %d\n", x, y);
}