#include <bits/stdc++.h>

using namespace std;

	
int main() {
	int ct;
	cin >> ct;
	vector<string> a;
	string aux; getline(cin, aux);
	string aux2 = "joulupukk";
	for(int i = 0; i < ct; i++) {
		getline(cin, aux);
		a.push_back(aux);
	}
	vector<vector<string> > b(int(a.size()));
	for(int i = 0; i < a.size(); i++) {
		stringstream ss;
		ss << a[i];
		string kappa;
		while(ss >> kappa) {
			b[i].push_back(kappa);		
		}
	}
	for(int i = 0; i < b.size(); i++) {
		for(int j = 0; j < b[i].size(); j++) {
			if(b[i][j].size()==10 || b[i][j].size()==11 && b[i][j][10]=='.'){
			bool ans = true;
			for(int z = 1; z < 9; z++) {
				if(b[i][j][z]!=aux2[z]) ans = false;
			}
			if(ans==true) {
				b[i][j][0] = 'J';
				b[i][j][9] = 'i';	
			}
		}
		}
	}
	for(int i = 0; i < b.size(); i++) {
		for(int j = 0; j < b[i].size(); j++) {
			cout << b[i][j] << " ";
		}
		cout << endl;
	}	
}