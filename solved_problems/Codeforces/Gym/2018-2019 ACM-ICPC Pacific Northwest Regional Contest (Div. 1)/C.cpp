#include <bits/stdc++.h>
#define mod 998244353
using namespace std;

typedef long long ll;
const int N = 1005;
unordered_map < ll, int > mapa;
ll v[N];
vector < ll > vet;
ll dp[N][N];

ll back(int pos, int k){
	if(k == 0) return 1LL;
	if(pos == vet.size()) return 0LL;
	ll &ans = dp[pos][k];
	if(ans != -1) return ans;
	ans = (((back(pos+1, k-1)%mod)*(mapa[vet[pos]]%mod))%mod + back(pos+1, k)%mod)%mod;
	return ans%mod;
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i=0; i<n; i++){
		scanf("%lld", &v[i]);
		mapa[v[i]]++;
	}
	sort(v, v+n);
	vet.push_back(v[0]);
	for (int i=1; i<n; i++){
		if(v[i] != v[i-1]) vet.push_back(v[i]);
	}
	memset(dp, -1, sizeof dp);
	printf("%lld\n", back(0, k));
}
