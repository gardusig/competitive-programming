#include <bits/stdc++.h>
using namespace std;

int main() {
	string a, b; cin >> a >> b;
	int ans = 0;
	for (int i = 0; i <= int(a.size()) - int(b.size()); ++i) {
		bool valid = true;
		for (int j = 0; j < int(b.size()); ++j)
			if (b[j] == a[i + j])
				valid = false;
		if (valid)
			++ans;
	}
	return printf("%d\n", ans), 0;
}