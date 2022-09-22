#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

void f() {
	string x;
	cin >> x;
	int n=x.size();
	if (n==1) {
		cout << x << endl;
		return;
	}
	int cur=1;
	for (;x[cur]>=x[cur-1]&&cur<n;cur++) {}
	if (cur==n) {
		cout << x << endl;
		return;
	}
	while (cur) {
		if (x[cur]<x[cur-1]) {
			for (int i=cur;i<n;i++) {
				x[i]='9';
			}
			x[cur-1]--;
			cur--;
		} else break;
	}
	for (cur=0;x[cur]=='0'&&cur<n;cur++) {}
	for (;cur<n;cur++) {
		printf("%c",x[cur]);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
