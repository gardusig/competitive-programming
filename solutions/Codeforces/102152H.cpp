#include<bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t-- > 0) {
		string s;
		cin >> s;
		bool flag = true;
		for (int i = 1; i < int(s.size()); i += 1) {
			if (s[i] == s[i- 1] + 1 or (s[i] == 'a' and s[i - 1] == 'z')) {
				continue;
			} else {
				flag = false;
			}
		}
		cout << (flag ? "YES" : "NO") << endl;
	}
}