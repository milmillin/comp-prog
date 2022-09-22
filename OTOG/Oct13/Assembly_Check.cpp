#include <cstdio>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main () {
	string x;
	string y;
	int a;
	vector<int> stk;
	while (cin >> x) {
		if (x=="PUH") {
			cin>>y;
			stk.push_back(a);
		} else if (x=="POP") {
			cin>>y;
			a=stk.back();
			stk.pop_back();
		} else if (x=="ADD") {
			int aa=stk.back();
			stk.pop_back();
			int bb=stk.back();
			stk.pop_back();
			stk.push_back(aa+bb);
		} else if (x=="ZER") {
			cin>>y;
			a=0;
		} else if (x=="ONE") {
			cin>>y;
			a=1;
		} else if (x=="PRN") {
			cin>>y;
			printf("%d\n",a);
		}
	}
	return 0;
}
