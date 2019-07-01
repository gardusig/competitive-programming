#include<bits/stdc++.h>
using namespace std;
int main(){
	int n; cin >> n;
	int a, b, x, y;
	while(n--){
		cin >> a >> b >> x >> y;
		cout << abs(a-x) + abs(b-y) << endl;
	}
	
	
}