#include <bits/stdc++.h>
using namespace std;
const int N = 112345;

int fingers[N], glove[N];

int main () {
	int t; scanf("%d", &t);
	while (t-- > 0) {
		int n; scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &fingers[i]);
		for (int i = 0; i < n; ++i)
			scanf("%d", &glove[i]);
		bool ans1 = true, ans2 = true;
		for (int i = 0; i < n; ++i)
			if (fingers[i] > glove[i])
				ans1 = false;
		reverse(glove, glove + n);
		for (int i = 0; i < n; ++i)
			if (fingers[i] > glove[i])
				ans2 = false;
		if (ans1 and ans2)
			printf("%s\n", "both");
		else if (ans1)
			printf("%s\n", "front");
		else if (ans2)
			printf("%s\n", "back");
		else
			printf("%s\n", "none");
	}
	return 0;
}