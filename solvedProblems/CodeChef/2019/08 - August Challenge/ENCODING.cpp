//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

const int MAX_SIZE = 112345;
const int MOD = 1000000000 + 7;
const pair< int, int > unvisited = {-1, -1};

class Solution {
  private:
  	int T;
  	int Nl;
  	string L;
   	int Nr;
  	string R;
  	int n;
  	string s;
  	int pot[MAX_SIZE];
  	pair< int, int > dp[MAX_SIZE][2][11];
  	
  	void build() {
  		pot[0] = 1;
  		for (int i = 1; i < MAX_SIZE; i += 1) {
  			pot[i] = (1LL * pot[i - 1] * 10) % MOD;
  		}
	}
  	
  	pair< int, int > solve(const int &i, const bool &less, const int &last) {
  		if (dp[i][less][last] != unvisited) {
  			return dp[i][less][last];
  		}
  		if (i == n) {
	  		dp[i][less][last] = {0, 1};
			return dp[i][less][last];
  		}
  		pair< int, int > ans(0, 0);
  		const int limit = less ? 9 : s[i] - '0';
  		for (int j = 0; j <= limit; j += 1) {
  			const pair< int, int > &nxt = solve(i + 1, less | (j < limit), j);
  			ans.first = (ans.first + nxt.first) % MOD;
  			ans.second = (ans.second + nxt.second) % MOD;
  			if (j != last) {
  				ans.first = (((1LL * j * nxt.second) % MOD) * pot[n - i - 1] + ans.first) % MOD;
  			}
  		}
  		dp[i][less][last] = ans;
  		return dp[i][less][last];
  	}

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      build();
    }
    
    void dpReset() {
		for (int i = 0; i <= n; i += 1) {
			for (int j = 0; j < 2; j += 1) {
				for (int k = 0; k < 11; k += 1) {
					dp[i][j][k] = unvisited;
				}
			}
		}
    }

    void main() {
		cin >> T;
		while (T-- > 0) {
			cin >> Nl >> L;
			cin >> Nr >> R;
			int ans = 0;
			s = R;
			n = Nr;
			dpReset();
			ans += solve(0, false, 10).first;
			int idx = -1;
			for (int i = int(L.size()) - 1; i >= 0; i -= 1) {
				if (L[i] > '0') {
					idx = i;
					break;
				}
			}
			s = L;
			s[idx] -= 1;
			for (int i = idx + 1; i < int(s.size()); i += 1) {
				s[i] = '9';
			}
			n = int(s.size());
			dpReset();
			ans -= solve(0, false, 10).first;
			if (ans < 0) {
				ans += MOD;
			}
			cout << ans << endl;
		}
    }
};

int main() {
  Solution().main();
  return 0;
}