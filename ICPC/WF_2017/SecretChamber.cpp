#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

bool pth[256][256];

bool f() {
	string x,y;
	cin>>x>>y;
	if (x.length()!=y.length()) return false;
	int n=x.length();
	for (int i=0;i<n;i++) {
		if (!pth[x[i]][y[i]]) return false;
	}
	return true;
}

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	char a,b;
	for (int i=0;i<n;i++) {
		scanf(" %c %c",&a,&b);
		pth[a][b]=true;
	}
	for (int i=0;i<256;i++) {
		pth[i][i]=true;
	}
	for (int k=0;k<256;k++) {
		for (int i=0;i<256;i++) {
			for (int j=0;j<256;j++) {
				pth[i][j]|=pth[i][k]&&pth[k][j];
			}
		}
	}
	while (q--) {
		printf("%s\n",f()?"yes":"no");
	}
	return 0;
}
