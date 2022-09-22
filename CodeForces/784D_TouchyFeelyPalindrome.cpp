#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main () {
	string x;
	cin>>x;
	int sum=0;
	for (int i=0;i<(int)x.size();i++) {
		sum+=x[i]-'0';
	}
	printf("%s\n",(sum==13)?"Yes":"No");
	return 0;
}
