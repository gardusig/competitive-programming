#include <bits/stdc++.h>
using namespace std;

namespace AhoCorasick {

const int M = 26;  // Number of possible characters (a-z)

int totalNodes = 0;

// Node structure for the Aho-Corasick automaton
struct Node {
  int id;
  Node* link;    // Failure link
  Node* nxt[M];  // Transitions
  set<int> end;  // Stores indices of patterns that end here

  Node() : link(nullptr), id(totalNodes++) {
    // Initialize all transitions to nullptr
    for (int i = 0; i < M; ++i) {
      nxt[i] = nullptr;
    }
  }

  // Add pattern to the trie
  void add(const string& pattern, int index, int pos) {
    if (pos == pattern.size()) {
      end.insert(index);
      return;
    }
    int ch = pattern[pos] - 'a';
    if (!nxt[ch]) nxt[ch] = new Node();
    nxt[ch]->add(pattern, index, pos + 1);
  }

  // Build the failure links
  void build() {
    queue<Node*> q;
    for (int i = 0; i < M; ++i) {
      if (nxt[i]) {
        nxt[i]->link = this;
        nxt[i]->end.insert(end.begin(), end.end());
        q.push(nxt[i]);
      } else {
        nxt[i] = this;
      }
    }
    while (!q.empty()) {
      Node* current = q.front();
      q.pop();
      for (int i = 0; i < M; ++i) {
        if (current->nxt[i]) {
          Node* fail = current->link;
          while (!fail->nxt[i]) fail = fail->link;
          fail = fail->nxt[i];
          current->nxt[i]->link = fail;
          current->nxt[i]->end.insert(fail->end.begin(), fail->end.end());
          q.push(current->nxt[i]);
        }
      }
    }
  }

  // Search for patterns in the text
  void search(const string& text, vector<vector<int>>& results) {
    Node* current = this;
    for (int i = 0; i < text.size(); ++i) {
      int ch = text[i] - 'a';
      while (!current->nxt[ch] && current != this) current = current->link;
      current = current->nxt[ch];
      for (int pattern_index : current->end)
        results[pattern_index].push_back(i);
    }
  }

  // Clear memory of nodes
  void clear() {
    for (int i = 0; i < M; ++i)
      if (nxt[i] && nxt[i]->id > id) nxt[i]->clear();
    delete this;
  }
};

// Build the Aho-Corasick automaton and search for patterns in the text
vector<vector<int>> buildAndSearch(const vector<string>& patterns,
                                   const string& text) {
  Node* root = new Node();
  vector<vector<int>> results(patterns.size());
  for (int i = 0; i < patterns.size(); ++i) root->add(patterns[i], i, 0);
  root->build();
  root->search(text, results);
  root->clear();
  return results;
}

}  // namespace AhoCorasick

void testAhoCorasick() {
  vector<string> patterns = {"ab", "bc", "abc"};
  string text = "abcabcab";

  vector<vector<int>> results = AhoCorasick::buildAndSearch(patterns, text);

  assert(results[0] ==
         vector<int>({2, 5}));  // Pattern "ab" found at indices 2 and 5
  assert(results[1] ==
         vector<int>({1, 4}));  // Pattern "bc" found at indices 1 and 4
  assert(results[2] == vector<int>({2}));  // Pattern "abc" found at index 2

  cout << "Aho-Corasick tests passed!" << endl;
}

int main() {
  testAhoCorasick();
  return 0;
}
