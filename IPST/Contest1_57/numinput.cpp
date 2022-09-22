#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[1010];

int pos[1010];
int num[1010];

int fact[1010];
int ifact[1010];
int mod=9901;

int poww(int x,int b) {
	if (b==0) return 1;
	if (b==1) return x;
	int a=poww(x,b/2);
	a*=a;
	a%=mod;
	if (b%2) {
		return (a*x)%mod;
	} else {
		return a;
	}
}

void init() {
	fact[0]=1;
	ifact[0]=1;
	fact[1]=1;
	ifact[1]=1;
	for (int i=2;i<1010;i++) {
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
		ifact[i]=poww(fact[i],mod-2);
	}
}

int main () {
	init();
	int n,m;
	scanf("%d%d",&n,&m);
	int sum=0;
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		sum+=tbl[i];
		tbl[i]+=tbl[i-1];
	}
	//int x;
	pos[0]=1;
	num[0]=1;
	for (int i=1;i<=m;i++) {
		scanf("%d",&pos[i]);
		num[i]=lower_bound(tbl+1,tbl+1+n,pos[i])-tbl;
		//printf("%d\n",num[i]);
	}
	pos[m+1]=sum;
	num[m+1]=n;
	long long ans=1;
	for (int i=0;i<=m;i++) {
		//printf("%d %d %d %d\n",pos[i],pos[i+1],num[i],num[i+1]);
		ans*=fact[pos[i+1]-pos[i]];
		ans%=mod;
		ans*=ifact[num[i+1]-num[i]];
		ans%=mod;
		ans*=ifact[pos[i+1]-pos[i]-num[i+1]+num[i]];
		ans%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
