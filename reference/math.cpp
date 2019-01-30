#include <bits/stdc++.h>
using namespace std;

vector< int > factorize(const auto &n, const auto &div) {
	vector< int > ans;
	for (int i = n; i > 1; i /= div[i])
		ans.push_back(div[i]);
	//~ set< int > s(ans.begin(), ans.end());
	//~ ans.assign(s.begin(), s.end());
	return ans;
}

int divisors_count(const auto &x) {
	int ans = 1;
	int before = -1;
	int current = 0;
	for (auto i : factorize(x)) {
		if (i == before)
			++current;
		else
			ans *= (current + 1), 
			current = 1, 
			before = i;
	}
	return ans * (current + 1);
}

vector<int> divisors_build(const auto &N) {
	vector<int> v(N);
	for (int i = 0; i < N; ++i)
		v[i] = i;
	for (int i = 2; i < N; ++i)
		if (v[i] == i)
			for (int j = i + i; j < N; ++j)
				if (v[j] == j)
					v[j] = i;
	return v;
}

vector<int> factorial_build(const auto &N, const auto &MOD) {
	vector<int> v(N);
	v[0] = 1;
	for (int i = 1; i < N; ++i)
		v[i] = (1LL * v[i-1] * i) % MOD;
	return v;
}

vector<int> inverse_factorial_build(const auto &N, const auto &MOD) {
	vector<int> v(N);
	v[0] = 1;
	for (int i = 1; i < N; ++i)
		v[i] = (1LL * v[i-1] * number_exponentiate(i, MOD - 2, MOD)) % MOD;
	return v;
}

int number_exponentiate(const auto &x, const auto &y, const auto &MOD) {
	if (y == 0)
		return 1;
	int ans = number_exponentiate(x, y >> 1, MOD);
	ans = (1LL * ans * ans) % MOD;
	if (y & 1)
		ans = (1LL * ans * x) % MOD;
	return ans;
}

int combination(const auto &n, const auto &k, const auto &MOD, const auto &fat, const auto &inv_fat) {
	int den = (1LL * inv_fat[k] * inv_fat[n - k]) % MOD;
	return (1LL * fat[n] * den) % MOD;
}

vector< vector<int> > combination_build(const auto &N, const auto &MOD) {
	vector< vector<int> > v;
	v.resize(N);
	for (int i = 0; i < int(v.size()); ++i)
		v[i].resize(N);
	for (int i = 0; i < N; ++i) {
		v[i][0] = 1;
		for (int j = 1; j < N; ++j) {
			if (j > i)
				v[i][j] = 0;
			else
				v[i][j] = (v[i-1][j-1] + v[i-1][j]) % MOD;
		}
	}
	return v;
}

int arithmetic_progression_element(const auto &value, const auto &pos_start, const auto &pos_finish, const auto &common_difference) {
	return value + (pos_finish - pos_start) * common_difference;
}

int arithmetic_progression_sum(const auto &value_start, const auto &value_finish, const auto &n) {
	return (n * (value_start + value_finish)) >> 1;
}

int geometric_progression_element(const auto &value, const auto &pos_start, const auto &pos_finish, const auto &common_ratio, const auto &MOD) {
	return value * exponentiate(common_ratio, pos_finish - pos_start, MOD);
}

int geometric_progression_sum(const auto &value, const auto &common_ratio, const auto &n) {
	int num = value * (1 - pow(common_ratio, n));
	int den = (1 - common_ratio);
	return num / den;
}

double simple_interest(const auto &capital, const auto &percentage, const auto &qtd) {
	return capital * (1.0 + (percentage * qtd));
}

double compound_interest(const auto &capital, const auto &percentage, const auto &qtd) {
	return capital * pow(1.0 + percentage, qtd);
}

int main () {
	return 0;
}