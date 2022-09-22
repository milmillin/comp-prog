#include <cstdio>
#include <string>
#include <iostream>

using namespace std;


int main () {
	int n;
	scanf("%d",&n);
	string x;
	cin>>x;
	int cnt=0;
	for (int i=0;i<n;i++) {
		if (x[i]=='<') cnt++;
		else break;
	}
	for (int i=n-1;i>=0;i--) {
		if (x[i]=='>') cnt++;
		else break;
	}
	printf("%d\n",cnt);
	return 0;
}
