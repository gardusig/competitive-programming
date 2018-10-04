#include <stdio.h>
#include <stdlib.h>

int main() {
	double A, B, C; scanf("%lf %lf %lf", &A, &B, &C);
	if (A > B) {
		int other = A;
		A = B;
		B = other;
	}
	if (B > C) {
		int other = B;
		B = C;
		C = other;
	}
	if (A > B) {
		int other = A;
		A = B;
		B = other;
	}
	printf("A: %.1lf, B: %.1lf, C: %.1lf\n", A, B, C);
}