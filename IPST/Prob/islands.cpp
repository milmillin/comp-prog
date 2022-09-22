#include <cstdio>
#include <cstring>

using namespace std;

int tbl[1010][600];
int mask[1010];

int mod=1000000007;

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	char x;
	int tmp=(1<<r)-1;
	for (int i=0;i<c;i++) {
		mask[i]=tmp;	
	}
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			scanf(" %c",&x);
			if (x=='#') {
				mask[j]^=(1<<i);
			}
		}
	}
	
	int sum=0;
	for (int i=1;i<=tmp;i++) {
		if ((i&mask[0])<i) continue;
		tbl[0][i]=1;
		sum++;
		//printf("%d\n",i);
	}

	for (int i=1;i<c;i++) {
		for (int j=1;j<=tmp;j++) {
			if ((j&mask[i])<j) continue;
			tbl[i][j]=1;
			for (int k=1;k<=tmp;k++) {
				if (j&k) {
					tbl[i][j]+=tbl[i-1][k];
					tbl[i][j]%=mod;
				}
			}	
			sum+=tbl[i][j];
			sum%=mod;	
		}
	}

	//for (int i=0;i<=tmp;i++) {
		//sum+=tbl[c-1][i];
		//sum%=mod;
	//}
	printf("%d\n",sum);
	return 0;
}
