#include <cstdio>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

void f() {
	string x,y;
	cin >> x >> y;
	for (int i=0;i<(int)x.size();i++) {
		if (x[i]=='@') x[i]='a';
		else if (x[i]=='!') x[i]='b';
		else if (x[i]=='#') x[i]='c';
		else if (x[i]=='$') x[i]='d';
	}
	for (int i=0;i<(int)y.size();i++) {
		if (y[i]=='@') y[i]='a';
		else if (y[i]=='!') y[i]='b';
		else if (y[i]=='#') y[i]='c';
		else if (y[i]=='$') y[i]='d';
	}
	regex ei(x);
	if (regex_match(y,ei)) printf("YES\n");
	else printf("NO\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}
