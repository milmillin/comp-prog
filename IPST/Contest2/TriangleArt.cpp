#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n,kk;
long long mem[200][200];
int mod=1000000007;
long long bit[200][200];
long long qs[200][200];

void update(int x,int y,long long val) {
	for (int i=x;i<200;i+=(i&-i)) {
		for (int j=y;j<200;j+=(j&-j)) {
			bit[i][j]+=val;
		}
	}
}

long long get(int x,int y) {
	long long sum=0;
	for (int i=x;i>0;i-=(i&-i)) {
		for (int j=y;j>0;j-=(j&-j)) {
			sum+=bit[i][j];
			sum%=mod;
		}
	}
	return sum;
}

long long recur(int a,int b) {
	//if ((a==1&&b==2)||(a==2&&b==1)) return 1;
	//if (mem[a][b]!=-1) return mem[a][b];
	long long sum=0;
	for (int i=2;i<=min(1+kk,a);i++) {
		sum+=1;
		//sum+=get(a-i,b-1);
		sum+=qs[a-i][b-1];
		/*
		for (int j=a-i;j>=0;j--) {
			for (int k=b-1;k>=0;k--) {
				sum+=recur(j,k);
				)	sum%=mod;
			}
		}
		*/
	}
	for (int i=2;i<=min(1+kk,b);i++) {
		sum+=1;
		sum+=qs[a-1][b-i];
		//sum+=get(a-1,b-i);
		/*
		for (int j=a-1;j>=0;j--) {
			for (int k=b-i;k>=0;k--) {
				sum+=recur(j,k);
				sum%=mod;
			}
		}
		*/
	}
	//sum+=recur(a-1,b);
	//sum%=mod;
	//sum+=recur(a,b-1);
	//sum%+mod;
	//update(a,b,sum);
	qs[a][b]=sum+qs[a-1][b]+qs[a][b-1]-qs[a-1][b-1];
	qs[a][b]%=mod;
	return sum;
}

int main () {
	scanf("%d%d",&n,&kk);
	memset(mem,-1,sizeof(mem));
	long long ans=0;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			ans+=recur(i,j);
			ans%=mod;
		}
	}
	printf("%I64d\n",ans);
	//printf("--%d\n",n);
	//for (int i=0;i<=n;i++) {
		//for (int j=0;j<=n;j++) {
			//printf("%I64d ",recur(i,j));
		//}
		//printf("\n");
	//}
	return 0;
}
