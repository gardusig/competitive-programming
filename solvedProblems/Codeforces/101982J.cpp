#include <bits/stdc++.h>
using namespace std;

int main(){
	long long n, s;
	cin >> n >> s;
	long long maior = 0, x;
	for (int i=0; i<n; i++){
		cin >> x;
		maior = max(maior, x);
	}
	long long ans = maior*s;
	if(ans%1000 == 0) cout << ans/1000 << endl;
	else cout << (ans/1000)+1LL << endl;
}
