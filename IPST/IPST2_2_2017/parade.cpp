#include <cstdio>
#include <vector>

using namespace std;

vector<int> pth[100100];
bool visit[100100];
long long fact[100100];

long long poww(int num,int deg) {
	if (deg==0) return 1;
	if (deg==1) return num;
	long long tmp=poww(num,deg/2);
	if (deg%2) {
		return (((tmp*tmp)%1000000007)*num)%1000000007;
	} else {
		return (tmp*tmp)%1000000007;
	}
}

int n;

long long dp[100100];
int cntt[100100];

int mod=1000000007;

void mic(int idx) {
	visit[idx]=true;

	int cnt=1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		mic(pth[idx][i]);
		cnt+=cntt[pth[idx][i]];
	}
	
	long long ans=fact[cnt-1];
	//printf("--%lld\n",ans);
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		ans*=poww(fact[cntt[pth[idx][i]]],mod-2);
		//printf("**%d\n",cntt[pth[idx][i]]);
		ans%=mod;
		ans*=dp[pth[idx][i]];
		ans%=mod;
	}

	dp[idx]=ans;
	cntt[idx]=cnt;

	//printf("%d %lld %d\n",idx,dp[idx],cntt[idx]);
	
	visit[idx]=false;
}

long long anss=0;

void chg(int idx) {
	anss+=dp[idx];
	//printf("** %d %lld\n",idx,dp[idx]);
	anss%=mod;
	visit[idx]=true;

	long long dpBak = dp[idx];
	int cntBak = cntt[idx];

	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		long long dpNewBak = dp[pth[idx][i]];
		int cntNewBak = cntt[pth[idx][i]];
		
		cntt[idx]-=cntt[pth[idx][i]];
	
		dp[idx]*=poww(fact[cntBak-1],mod-2);
		dp[idx]%=mod;
	
		dp[idx]*=fact[cntt[idx]-1];
		dp[idx]%=mod;
	
		dp[idx]*=fact[cntNewBak];
		dp[idx]%=mod;
	
		dp[idx]*=poww(dpNewBak,mod-2);
		dp[idx]%=mod;

		cntt[pth[idx][i]]+=cntt[idx];

		//printf("++ %lld %d %lld %d\n", dp[pth[idx][i]], cntNewBak, fact[cntNewBak-1], cntt[pth[idx][i]]);

		dp[pth[idx][i]]*=poww(fact[cntNewBak-1],mod-2);
		dp[pth[idx][i]]%=mod;
		
		dp[pth[idx][i]]*=fact[cntt[pth[idx][i]]-1];
		dp[pth[idx][i]]%=mod;
	
		//printf("++ %lld\n", dp[pth[idx][i]]);

		dp[pth[idx][i]]*=poww(fact[cntt[idx]],mod-2);
		dp[pth[idx][i]]%=mod;
		
		dp[pth[idx][i]]*=dp[idx];
		dp[pth[idx][i]]%=mod;

		//printf("-- %d %lld %d %lld\n",cntt[idx],dp[idx],cntt[pth[idx][i]],dp[pth[idx][i]]);

		chg(pth[idx][i]);
		
		dp[idx]=dpBak;
		cntt[idx]=cntBak;
		dp[pth[idx][i]]=dpNewBak;
		cntt[pth[idx][i]]=cntNewBak;
	}

	visit[idx]=false;
}


int main() {
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	fact[0]=1;
	for (int i=1;i<=n;i++) {
		fact[i]=(fact[i-1]*i)%1000000007;
	}

	//for (int i=0;i<n;i++) {
		//mic(i);
		//anss+=dp[i];
		//printf("%lld\n",dp[i]);
	//}

	mic(0);
	chg(0);
	//anss+=dp[0];

	printf("%lld\n",anss);

	return 0;
}
