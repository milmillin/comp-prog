#include <cstdio>
#include <cstdlib>

using namespace std;

int tbl[100010];

int main () {
	freopen("taming.in","r",stdin);
	freopen("taming.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	tbl[0]=0;
	int cur=(tbl[n-1]==-1)?-1:tbl[n-1]-1;
	for (int i=n-2;i>=0;i--) {
		//printf("-- %d\n",cur);
		if (cur!=-1) {
			if (tbl[i]==-1) {
				tbl[i]=cur;
			} else if (cur!=tbl[i]) {
				printf("-1\n");
				return 0;
			}
			cur--;
		} else {
			if (tbl[i]!=-1) {
				cur=tbl[i]-1;
			}
		}
	}
	int zr=0;
	int oo=0;
	for (int i=0;i<n;i++) {
		//printf("%d ",tbl[i]);
		if (tbl[i]==0) zr++;
		if (tbl[i]==-1) oo++;
	}
	printf("%d %d\n",zr,zr+oo);
	return 0;
}
