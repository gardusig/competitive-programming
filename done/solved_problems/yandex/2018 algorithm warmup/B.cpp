#include <bits/stdc++.h>
using namespace std;

int main () {
	vector<string> ans;
	string s; cin >> s;
	for (int i = 0; i < int(s.size()); ++i) {
		for (int j = i + 1; j < int(s.size()) and j < i + 3; ++j) {
			string kappa = s.substr(i, j - i + 1);
			string keepo = kappa; reverse(keepo.begin(), keepo.end());
			if (kappa == keepo)
				ans.push_back(kappa);
		}
	}
	if (!int(ans.size()))
		return !printf("%d\n", -1);
	string best = "kappppppppppppppppppppppppppppppppppppppppppa";
	for (auto i : ans)
		if (int(i.size()) < int(best.size()) or (int(i.size()) == int(best.size()) and i < best))
			best = i;
	return !printf("%s\n", best.c_str());
}