#include <cstdio>

using namespace std;

int mod=1000003;

long long poww(int i,int j) {
	if (j==0) return 1;
	if (j==1) return i;
	if (j%2) {
		long long tmp=poww(i,j/2);
		return (((tmp*tmp)%mod)*i)%mod;
	} else {
		long long tmp=poww(i,j/2);
		return (tmp*tmp)%mod;
	}
}

int ncr(int n,int r) {
	long long sum=1;
	for (int i=n;i>r;i--) {
		sum*=i;
		sum%=mod;
		//printf("%d ",i);
	}
	//printf("\n");
	long long divv=1;
	for (int i=2;i<=n-r;i++) {
		//divv*=i;
		//divv%=mod;
		//printf("%d ",i);	
		sum*=poww(i,mod-2);
		sum%=mod;
	}
	//printf("\n");
	//sum*=poww(divv,mod-2);
	return sum%mod;
}

int main () {
	int n,r;
	scanf("%d%d",&n,&r);
	printf("%d\n",ncr(n,r));
	return 0;
}
