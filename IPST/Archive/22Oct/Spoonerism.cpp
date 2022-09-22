#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void f() {
	string x;
	cin>>x;
	string tmp="";
	//printf("%d\n",tmp.length());
	vector<string> stk;
	for (int i=0;i<(int)x.length();i++) {
		if (x[i]=='a'||x[i]=='e'||x[i]=='i'||x[i]=='o'||x[i]=='u') {
			tmp+=x[i];
		} else {
			if (tmp.size()) {
				stk.push_back(tmp);
				tmp="";
			}
		}
	}
	if (tmp.size()) stk.push_back(tmp);
	bool printFront=false;
	bool print=false;
	int cur=1;
	for (int i=0;i<(int)x.length();i++) {
		if (x[i]=='a'||x[i]=='e'||x[i]=='i'||x[i]=='o'||x[i]=='u') {
			if (!printFront) {
				cout<<stk.back();
				printFront=true;
				print=true;
			} else if (!print) {
				if (cur==stk.size()-1) cur=0;
				cout<<stk[cur];
				cur++;
				
				print=true;
			}
		} else {
			print=false;
			cout<<x[i];
		}
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
