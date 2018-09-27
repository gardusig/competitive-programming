#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10, M = 30;

int n;
char s[N];
double ans;

struct node {
	int total;
	int finish;
	node *nxt[M];
	node () {
		total = finish = 0;
		for (int i = 0; i < M; ++i)
			nxt[i] = NULL;
	}
	void add (const int i) {
		if (i == strlen(s)) {
			++finish;
			return;
		}
		int j = s[i] - 'a';
		if (!nxt[j])
			++total, nxt[j] = new node();
		nxt[j]->add(i + 1);
	}
	void count (const int current) {
		ans += (current * finish);
		for (int i = 0; i < M; ++i)
			if (nxt[i])
				nxt[i]->count(current + ((total > 1) or finish));
	}
};

int main () {
	while (scanf("%d", &n) != EOF) {
		node *root = new node();
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			root->add(0);
		}
		ans = 0;
		root->total = 2, root->count(0);
		printf("%.2lf\n", ans / double(n));
	}
	return 0;
}