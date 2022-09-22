#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char x[1010];

int tbl[1010][26][2];

int getTurn(int a,int b) {
	if (b<a) b+=26;
	return min(b-a,26-b+a);
}

void f() {
	scanf("%s",x);
	int len = strlen(x);
	int new1,new2;
	int ans=2e9;
	for (int i=0;i<len;i++) {
		for (int j=0;j<26;j++) {
			if (!i) {
				tbl[i][j][0]=getTurn('A',x[i])+getTurn('A',j+'A');
				tbl[i][j][1]=getTurn('A',x[i])+getTurn('A',j+'A');
			} else {
				tbl[i][j][0]=2e9;
				tbl[i][j][1]=2e9;
				for (int k=0;k<26;k++) {
					new1=min(getTurn(x[i-1],x[i])+getTurn(k,j)+tbl[i-1][k][0],getTurn(k+'A',x[i])+getTurn(x[i-1],j+'A')+tbl[i-1][k][1]);
					new2=min(getTurn(x[i-1],j+'A')+getTurn(k+'A',x[i])+tbl[i-1][k][0],getTurn(k,j)+getTurn(x[i-1],x[i])+tbl[i-1][k][1]);
					tbl[i][j][0]=min(tbl[i][j][0],new1);
					tbl[i][j][1]=min(tbl[i][j][1],new2);
				}
			}
			//printf("%d,%d ",tbl[i][j][0],tbl[i][j][1]);
			if (i==len-1) ans=min(ans,min(tbl[i][j][0],tbl[i][j][1]));
		}
		//printf("\n");
	}
	printf("%d\n",ans);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
