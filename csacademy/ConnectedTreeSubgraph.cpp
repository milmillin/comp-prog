#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

vector<int> pth[100100];

int cnt[100100];
long long ways[100100];
long long mod=1000000007;
long long fact[100100];
long long inv[100100];

long long poww(long long x,int b) {
	if (b==0) return 1;
	if (b==1) return x;
	long long tmp=poww(x,b/2);
	if (b%2) {
		return ((tmp*tmp)%mod*x)%mod;
	} else {
		return (tmp*tmp)%mod;
	}
}

void init() {
	fact[0]=1;
	inv[0]=1;
	for (int i=1;i<100100;i++) {
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
		inv[i]=poww(fact[i],mod-2);
		assert(inv[i]>0);
	}
}

void dfs(int idx,int par) {
	int c=1;
	long long w=1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		dfs(pth[idx][i],idx);
		c+=cnt[pth[idx][i]];
		w*=inv[cnt[pth[idx][i]]];
		w%=mod;
		w*=ways[pth[idx][i]];
		w%=mod;
	}
	w*=fact[c-1];
	w%=mod;
	ways[idx]=w;
	cnt[idx]=c;
}

long long ans;

void chg(int idx,int par) {
	ans+=ways[idx];
	ans%=mod;
	int tc=cnt[idx];
	long long tw=ways[idx];
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		ways[idx]*=inv[cnt[idx]-1];
		ways[idx]%=mod;
		cnt[idx]-=cnt[pth[idx][i]];
		ways[idx]*=fact[cnt[idx]-1];
		ways[idx]%=mod;
		ways[idx]*=fact[cnt[pth[idx][i]]];
		ways[idx]%=mod;
		ways[idx]*=poww(ways[pth[idx][i]],mod-2);
		ways[idx]%=mod;
		
		int ttc=cnt[pth[idx][i]];
		long long ttw=ways[pth[idx][i]];
		ways[pth[idx][i]]*=inv[cnt[pth[idx][i]]-1];
		ways[pth[idx][i]]%=mod;
		cnt[pth[idx][i]]+=cnt[idx];
		ways[pth[idx][i]]*=fact[cnt[pth[idx][i]]-1];
		ways[pth[idx][i]]%=mod;
		ways[pth[idx][i]]*=ways[idx];
		ways[pth[idx][i]]%=mod;
		ways[pth[idx][i]]*=inv[cnt[idx]];
		ways[pth[idx][i]]%=mod;

		chg(pth[idx][i],idx);
		
		cnt[pth[idx][i]]=ttc;
		ways[pth[idx][i]]=ttw;
		cnt[idx]=tc;
		ways[idx]=tw;
	}
}

int main () {
	init();
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	dfs(1,0);
	chg(1,0);
	printf("%lld\n",ans);
	return 0;
}
