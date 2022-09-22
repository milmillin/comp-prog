#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main () {
	string x;
	cin>>x;
	int a=0,b=0;
	bool isAdd=true;
	for (int i=0;i<(int)x.size();i++) {
		if (x[i]=='+') {
			if (isAdd) a+=b;
			else a-=b;
			b=0;
			isAdd=true;
		} else if (x[i]=='-') {
			if (isAdd) a+=b;
			else a-=b;
			b=0;
			isAdd=false;
		} else {
			b*=10;
			b+=x[i]-'0';		
			//printf("%d\n",b);
		}
	}
	if (isAdd) a+=b;
	else a-=b;
	//printf("%d\n",a);

	if (a==0) {
		for (int i=0;i<48;i++) {
			printf("+");
		}
		printf(".\n");
		return 0;	
	}


	vector<int> ans;
	while (a) {
		ans.push_back(a%10);
		a/=10;
	}
	for (int i=ans.size()-1;i>=0;i--) {
		for (int j=0;j<ans[i]+48;j++) {
			printf("+");
		}
		printf(".");
		if (i) printf(">");
	}
	printf("\n");
	return 0;
}
