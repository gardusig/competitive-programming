#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int N = 1123456;
const int MOD = 1000000000 + 7;

ll fat[N];
int fst_div[N];

vector<int> factorize (const int &x) {
	vector<int> ans;
	//~ ans.push_back(1);
	for (int i = x; i > 1; i /= fst_div[i])
		ans.push_back(fst_div[i]);
	return ans;
}

int count_divisors (const int &x) {
	int ans = 1;
	int before = -1;
	int current = 0;
	for (auto i : factorize(x)) {
		if (i == before)
			++current;
		else
			ans *= (current + 1), current = 1, before = i;
	}
	return ans * (current + 1);
}

void build_sieve () {
	for (int i = 1; i < N; ++i)
		fst_div[i] = i;
	for (int i = 2; i < N; ++i)
		if (fst_div[i] == i)
			for (int j = i; j < N; j += i)
				fst_div[j] = min(fst_div[j], i);
}

void build_factorial () {
	fat[0] = 1;
	for (int i = 1; i < N; ++i)
		fat[i] = (fat[i-1] * i) % MOD;
}

ll exponentiate (const ll &x, const ll &y, const ll &MOD) {
	if (!y)
		return 1;
	ll ans = exponentiate(x, y >> 1, MOD);
	ans = (ans * ans) % MOD;
	if (y & 1)
		ans = (ans * x) % MOD;
	return ans;
}

//~ comb(x, y) = comb(x - 1, y) + comb(x - 1, y - 1)
ll combination (const ll &x, const ll &y, const ll &MOD) {
	if (x < 1 or y < 1 or x < y)
		return 0;
	ll num = fat[x];
	ll den = (inv[y] * inv[x - y]) % MOD;
	ll ans = (num * den) % MOD;
	return ans;
}

void aritmetic_progression (const ll &a1, const ll &n, const ll &r) {
	ll n_element = a1 + ((n - 1) * r);
	ll sum = ((a1 + n_element) * n) >> 1;
}

void geometric_progression (const ll &a1, const ll &n, const ll &r) {
	ll n_element = a1 * exponentiate(r, n - 1);
	ll sum = (a1 * (pow(r, n) - 1)) / (r - 1);
}

double simple_interest (const double &capital, const double &percentage, const double &qtd) {
	return capital * percentage * qtd;
}

double compound_interest (const double &capital, const double &percentage, const double &qtd) {
	return capital * pow(1.0 + percentage, qtd);
}

int main () {
	build_sieve();
	int x; scanf("%d", &x);
	printf("%d has %d divisors\n", x, count_divisors(x));
	printf("factors:");
	for (auto i : factorize(x))
		printf(" %d", i);
	puts("");

	build_factorial();
	ll n, k; scanf("%lld %lld", &n, &k);
	printf("%lld\n", combination(n, k));
	return 0;
}