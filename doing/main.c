#include <stdio.h>
#include <stdlib.h>

int main() {
	int n;
	scanf("%d", &n);
	int i = 1;
	while (i <= n) {
		printf("%d / %d\n", 1, (i * 4 - 3));
		i = i + 1;
	}
	return 0;
}
