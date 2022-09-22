#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main () {
	string x;
	cin >> x;
	int maxx=0;
	int last=-1;
	for (int i=0;i<x.size();i++) {
		if (x[i]=='A'||x[i]=='E'||x[i]=='O'||x[i]=='U'||x[i]=='I'||x[i]=='Y') {
			maxx=max(maxx,i-last);
			last=i;
		}
	}
	maxx=max(maxx,(int)x.size()-last);
	printf("%d\n",maxx);
	return 0;
}
