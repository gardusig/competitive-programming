#include <bits/stdc++.h>
using namespace std;

const int N = 26;

class node {
public:
  bool win;
  bool lose;
  node *nxt[N];

  node() {
    this->win = false;
    this->lose = false;
    for (int i = 0; i < N; i += 1) {
      this->nxt[i] = NULL;
    }
  }

  void insert(const auto &i, const auto &s) {
    if (i == int(s.size())) {
      return;
    }
    int j = s[i] - 'a';
    if (this->nxt[j] == NULL) {
      this->nxt[j] = new node();
    }
    this->nxt[j]->insert(i + 1, s);
  }

  void build() {
    bool leaf = true;
    for (int i = 0; i < N; i += 1) {
      if (this->nxt[i] != NULL) {
        leaf = false;
        this->nxt[i]->build();
        this->win |= (this->nxt[i]->win == false);
        this->lose |= (this->nxt[i]->lose == false);
      }
    }
    if (leaf == true) {
      this->win = false;
      this->lose = true;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, k;
  cin >> n >> k;
  node *trie = new node();
  while (n-- > 0) {
    string s;
    cin >> s;
    trie->insert(0, s);
  }
  trie->build();
  if (trie->win == false or (trie->lose == false and (k % 2) == 0)) {
    cout << "Second" << endl;
  } else {
    cout << "First" << endl;
  }
  return 0;
}