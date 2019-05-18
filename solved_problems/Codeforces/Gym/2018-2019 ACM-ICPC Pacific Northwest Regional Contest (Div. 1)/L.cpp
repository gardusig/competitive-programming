#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int vet[N][2];

int main(){
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; i++){
		scanf("%d %d", &vet[i][0], &vet[i][1]);
	}
	int ans = -1;
	for (int cont=0; cont <= n; cont++){
		int qtd = 0;
		for (int i=0; i<n; i++){
			if(cont >= vet[i][0] && cont <= vet[i][1]) qtd++;
		}
		if(qtd == cont) ans = cont;
	}
	printf("%d\n", ans);
}
