#include <cstdio>

using namespace std;

int par[100100];

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	int a,b;
	char x;
	for (int i=1;i<=n;i++) {
		par[i]=i;
	}
	for (int i=0;i<q;i++) {
		scanf(" %c%d%d",&x,&a,&b);
		if (x=='c') {
			if (findPar(a)==findPar(b)) continue;
			par[findPar(a)]=findPar(b);
		} else {
			printf("%s\n",(findPar(a)==findPar(b))?"yes":"no");
		}
	}
	return 0;
}
