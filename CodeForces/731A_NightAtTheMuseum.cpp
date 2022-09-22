#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main () {
	string x;
	cin >> x;
	int ans=0;
	int last='a';
	for (int i=0;i<x.length();i++) {
		if (x[i]>last) {
			ans+=min(x[i]-last,last+26-x[i]);
			//printf("-%d\n",min(x[i]-last,last+26-x[i]));
		} else {
			ans+=min(last-x[i],x[i]+26-last);
			//printf("-%d\n",min(last-x[i],x[i]+26-last));
		}
		last=x[i];
	}
	printf("%d\n",ans);
	return 0;
}
