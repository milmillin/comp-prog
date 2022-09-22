#include <cstdio>
#include <cstring>

using namespace std;

long long mem[1010][1010][3][8];
long long sum[1010][5][110];
const int mod = 1000000007;

int main () {
	int n,a,b,c;
	scanf("%d%d%d%d",&n,&a,&b,&c);
	memset(mem,0,sizeof(mem));
	memset(sum,0,sizeof(sum));
	mem[1][1][0][1]=1;
	sum[1][0][1]=1;
	for (int i=2;i<=n;i++) {
		for (int k=1;k<8;k++) {
			for (int l=1;l<8;l++) {
				if ((l|1)==k) {
					//a
					//printf("a %d %d %d\n",i,k,l);
					mem[i][1][0][k]+=sum[i-1][2][l];
				}
				if ((l|2)==k) {
					//b
				//	printf("b %d %d %d\n",i,k,l);
					mem[i][1][1][k]+=sum[i-1][0][l];
				}
				if ((l|4)==k) {
					//c
					//printf("c %d %d %d\n",i,k,l);
					mem[i][1][2][k]+=sum[i-1][0][l]+sum[i-1][1][l];
				}
			}
			sum[i][0][k]=mem[i][1][0][k]%mod;
			sum[i][1][k]=mem[i][1][1][k]%mod;
			sum[i][2][k]=mem[i][1][2][k]%mod;
		}

		for (int j=2;j<=a;j++) {
			//a
			for (int k=1;k<8;k++) {
				if ((k&1)==0) continue;
				//mem[i][j][0][k]+=mem[i-1][j-1][0][k];
				for (int l=1;l<8;l++) {
					if ((l|1)!=k) continue;
					//printf("a %d %d %d %d\n",i,j,k,l);
					//mem[i][j][0][k]+=sum[i-j][2][l];
					mem[i][j][0][k]+=mem[i-1][j-1][0][l];
				}
				sum[i][0][k]+=mem[i][j][0][k];
				sum[i][0][k]%=mod;
				//printf("%d\n",sum[i][0][k]);			
			}
		}
		for (int j=2;j<=b;j++) {
			//b
			for (int k=1;k<8;k++) {
				if ((k&2)==0) continue;
				//mem[i][j][1][k]+=mem[i-1][j-1][1][k];
				for (int l=1;l<8;l++) {
					if ((l|2)!=k) continue;
					//printf("b %d %d %d %d\n",i,j,k,l);
					//mem[i][j][1][k]+=sum[i-j][0][l];
					mem[i][j][1][k]+=mem[i-1][j-1][1][l];
					//printf("%d %d\n",mem[i-1][j-1][1][l],sum[i-j][0][l]);
				}
			//	printf("%d\n",sum[i][1][k]);
				sum[i][1][k]+=mem[i][j][1][k];
				sum[i][1][k]%=mod;
			//	printf("%d\n",sum[i][1][k]);				
			}
		}
		for (int j=2;j<=c;j++) {
			for (int k=1;k<8;k++) {
				if ((k&4)==0) continue;
				//mem[i][j][2][k]=mem[i-1][j-1][2][k];
				for (int l=1;l<8;l++) {
					if ((l|4)!=k) continue;
					//printf("c %d %d %d %d\n",i,j,k,l);
					//mem[i][j][2][k]+=sum[i-j][1][l]+sum[i-j][0][l];
					mem[i][j][2][k]+=mem[i-1][j-1][2][l];
				}
				sum[i][2][k]+=mem[i][j][2][k];
				sum[i][2][k]%=mod;
				//printf("%d\n",sum[i][2][k]);				
			}
		}
		/*
		for (int k=0;k<3;k++) {
			for (int j=0;j<8;j++) {
				printf("%d ",sum[i][k][j]);
			}
			printf("\n");
		}
		printf("\n");
		//printf("%d %d %d\n",sum[i][0][7],sum[i][1][7],sum[i][2][7]);
		*/
	}
	printf("%d\n",(sum[n][0][7]+sum[n][1][7]+sum[n][2][7])%mod);
	return 0;
}
