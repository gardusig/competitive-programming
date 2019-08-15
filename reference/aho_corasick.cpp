#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
const int M = 150;

int total;
string s, x, y;
int dp[N][N][N];

struct node {
	int id;
	bool end;
	node *link;
	node *nxt[M];

	node () {
		end = false;
		link = NULL;
		id = total++;
		for (int i = 0; i < M; ++i)
			nxt[i] = NULL;
	}
	
	void add (const int &i) {
		if (i == s.length()) {
			end = true;
			return;
		}
		if (!nxt[s[i]])
			nxt[s[i]] = new node();
		nxt[s[i]]->add(i + 1);
	}
	
	void build () {
		queue<node*> q;
		for (int i = 0; i < M; ++i) {
			if (nxt[i])
				nxt[i]->link = this, q.push(nxt[i]);
			else
				nxt[i] = this;
		}
		while (q.size()) {
			node *current = q.front(); q.pop();
			for (int i = 0; i < M; ++i) {
				if (current->nxt[i]) {
					node *fail = current->link;
					while (!fail->nxt[i])
						fail = fail->link;
					fail = fail->nxt[i];
					current->nxt[i]->link = fail;
					q.push(current->nxt[i]);
				}
			}
		}
	}
	
	node* get (const char &c) {
		node *current = this;
		while (!current->nxt[c] and current != current->link)
			current = current->link;
		if (current->nxt[c])
			current = current->nxt[c];
		return current;
	}
};

int solve (const int &i, const int &j, const int &k, node *current) {
	if (i == x.size() or (j == y.size()))
		return dp[i][j][k] = 0;
	if (dp[i][j][k] != -1)
		return dp[i][j][k];
	int ans = 0;
	ans = max(ans, solve(i + 1, j, k, current));
	ans = max(ans, solve(i, j + 1, k, current));
	current = current->get(x[i]);
	if (x[i] == y[j] and !current->end)
		ans = max(ans, 1 + solve(i + 1, j + 1, current->id, current));
	return dp[i][j][k] = ans;
}

void path (const int &i, const int &j, const int &k, node *current) {
	if (i == x.size() or (j == y.size()))
		return;
	if (dp[i][j][k] == dp[i + 1][j][k]) {
		path(i + 1, j, k, current);
		return;
	}
	if (dp[i][j][k] == dp[i][j + 1][k]) {
		path(i, j + 1, k, current);
		return;
	}
	current = current->get(x[i]);
	s.push_back(x[i]);
	path(i + 1, j + 1, current->id, current);
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> x >> y >> s;
	total = 0;
	node *root = new node();
	root->add(0);
	root->build();
	memset(dp, -1, sizeof dp);
	int ans = solve(0, 0, 0, root);
	if (!ans) {
		cout << 0 << '\n';
		return 0;
	}
	s.clear();
	path(0, 0, 0, root);
	cout << s << '\n';
	return 0;
}