//~ QUESTÃO 01

#include <stdio.h>
#include <stdlib.h>

int main () {
	double a[51];
	int n; scanf("%d", &n);
	int i;
	double soma = 0;
	for (i = 0; i < n; ++i) {
		scanf("%lf", &a[i]);
		soma += a[i];
	}
	double media = soma / (double)n;
	printf("media aritmetica: %.10lf\n", media);
	int acima = 0;
	for (i = 0; i < n; ++i)
		if (a[i] > media)
			acima += 1;
	printf("numeros acima da média: %d\n", acima);
	double b[51];
	for (i = 0; i < n; ++i) {
		b[i] = a[i] - ((double)acima / media);
		printf("%.2lf ", b[i]);
	}
	printf("\n");
	double resultado = 0;
	for (i = 0; i < n; ++i)
		resultado += (a[i] * b[i]);
	printf("%.10lf\n", resultado);
	return 0;
}