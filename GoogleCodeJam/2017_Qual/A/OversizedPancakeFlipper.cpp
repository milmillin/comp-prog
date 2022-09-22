#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

void f() {
	string x;
	cin >> x;
	int k;
	scanf("%d",&k);
	int n=x.size();
	int cnt=0;
	for (int i=0;i<n-k+1;i++) {
		if (x[i]=='+') continue;
		cnt++;
		for (int j=i;j<i+k;j++) {
			if (x[j]=='+') x[j]='-';
			else x[j]='+';
		}
	}
	bool yes=true;
	for (int i=n-k+1;i<n;i++) {
		if (x[i]=='-') {
			yes=false;
			break;
		}
	}
	//cout << x << endl;
	if (yes) printf("%d\n",cnt);
	else printf("IMPOSSIBLE\n");
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
