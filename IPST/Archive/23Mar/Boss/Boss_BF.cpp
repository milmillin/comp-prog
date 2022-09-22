#include <cstdio>

using namespace std;

int par[100100];
bool sel[100100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int x;
	for (int i=2;i<=n;i++) {
		scanf("%d",&x);
		par[i]=x;
	}
	sel[1]=true;
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		if (a==1) sel[b]=true;
		if (a==2) sel[b]=false;
		if (a==3) {
			while (!sel[b]) {
				b=par[b];
			}
			printf("%d\n",b);
		}
	}
	return 0;
}
