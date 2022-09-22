#include <cstdio>

using namespace std;

int tbl[1200000];
int qs[1200000];

int main () {
	int n;
	scanf("%d",&n);
	int m = 1<<n;
	int zr=-1;
	int xx=-1;
	for (int i=1;i<=m;i++) {
		scanf("%d",&tbl[i]);
		//tbl[i]=tbl[i-1]^tbl[i];
		qs[i]=qs[i-1]^tbl[i];
		if (tbl[i]==0) zr=i;
		if (tbl[i]==m-1) xx=i;
	}
	printf("%d\n",m*(m+1)/2);
	int cnt=0;
	for (int i=1;i<=m;i++) {
		for (int j=i;j<=m;j++) {
			//if ((qs[j]^qs[i-1])==0) cnt--;
			int s = qs[j]^qs[i-1];
			if (s==m-1) {
				cnt++;
				continue;
			}
			bool eiei=false;
			for (int k=i;k<=j;k++) {
				bool work=true;
				int r=s^tbl[k]^(m-1);
				for (int p=i;p<=j;p++) {
					if (tbl[p]==r) {
						work=false;
						break;
					}
				}
				if (work) {
					eiei=true;
					cnt++;
					break;
				}
			}
			if (eiei) continue;
			for (int k=i;k<=j;k++) {
				printf("%d ",tbl[k]);
			}
			printf("--> %d %c\n",s,(eiei)?'y':'n');
		}
	}
	printf("%d\n",cnt);
	return 0;
}
