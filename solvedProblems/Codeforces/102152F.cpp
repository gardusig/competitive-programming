#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	while (n-- > 0){
		string str;
		cin >> str;
		bool flag = true;
		int cont=1;
		if(str[0] >= 'A' && str[0] <= 'Z') {
			flag = false;
		}
		else {
			for (int i=0; i<str.size(); i++){
				if(str[i] >= 'A' && str[i] <= 'Z') cont++;
				else if(!(str[i] >= 'a' && str[i] <= 'z')){
					flag = false;
					break;
				}
			}
		}
		if(flag == false) puts("NO");
		else if(cont <= 7) puts("YES");
		else puts("NO");
	}
}