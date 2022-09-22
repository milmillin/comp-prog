#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

long long tbl[4010][4010];
long long fact[8010];
long long iFact[8010];
long long mod=1000000007;

long long poww(long long x,long long y) {
	long long res = 1;
	while(y)
	{
		if(y & 1) res = (res * x) % mod; 
		x = x * x % mod;
		y = y >> 1;
	}
	return res;

	//if (x==0) return 1;
	//if (x==1) return b;
	//long long tmp = poww(b,x/2);
	//tmp=(tmp*tmp)%mod;
	//if (x%2) {
		//return (tmp*b)%mod;
	//} else {
		//return tmp;
	//}	
}

int main() {
	int n;
	scanf("%d",&n);
	fact[0]=1;
	for (int i=1;i<8010;i++) {
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
		iFact[i]=poww(fact[i],mod-2);
		//printf("%lld\n",fact[i]);
	}
	//printf("%lld\n",iFact[2]);
	int a,b;
	long long ans=0;
	//int c,d;
	//scanf("%d%d%d%d",&a,&b,&c,&d);
	//printf("%d %d %lld %lld %lld\n",a+c,b+d,fact[a+b+c+d],iFact[a+c],iFact[b+d]);
	vector<pair<int,int>> ttt;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		ans-=(((fact[2*a+2*b]*iFact[2*a])%mod)*iFact[2*b])%mod;
		ans%=mod;
		//printf("%lld\n",(((fact[2*a+2*b]*iFact[2*a])%mod)*iFact[2*b])%mod);
		tbl[2001-a][2001-b]++;
		ttt.push_back({2001+a,2001+b});
	}
	for (int i=1;i<4010;i++) {
		for (int j=1;j<4010;j++) {
			tbl[i][j]+=(tbl[i-1][j]+tbl[i][j-1])%mod;
			tbl[i][j]%=mod;
		}
	}
	for (int i=0;i<n;i++) {
		ans+=tbl[ttt[i].first][ttt[i].second];
		ans%=mod;
	}
	ans*=iFact[2];
	ans%=mod;
	printf("%lld\n",ans);
	return 0;
}
