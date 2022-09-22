#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int r[300];
long long f[300];
long long cost[300][300];
long long mic[300][300];
long long base[300];
long long endd[300];

int d,k;

long long dp(int idx,int kk) {
	if (kk==1) {
		return base[idx];
	}
	if (mic[idx][kk]!=-1) return mic[idx][kk];
	mic[idx][kk]=4e18;
	for (int i=0;i<idx;i++) {
		mic[idx][kk]=min(mic[idx][kk],dp(i,kk-1)+cost[i][idx]);
	}
	return mic[idx][kk];
}

long long sq(long long val) {
	return val*val;
}

int main () {
	scanf("%d%d",&d,&k);
	for (int i=0;i<d;i++) {
		scanf("%d%lld",&r[i],&f[i]);
	}
	for (int i=0;i<256;i++) {
		for (int j=i+2;j<256;j++) {
			cost[i][j]=0;
			for (int k=0;k<d;k++) {
				if (r[k]<=i) continue;
				if (r[k]>=j) continue;
				cost[i][j]+=f[k]*min(sq(r[k]-i),sq(r[k]-j));
			}
		}
	}
	for (int i=0;i<256;i++) {
		for (int j=0;j<d;j++) {
			if (r[j]>=i) continue;
			base[i]+=f[j]*sq(r[j]-i);
		}
	}
	for (int i=0;i<256;i++) {
		for (int j=0;j<d;j++) {
			if (r[j]<=i) continue;
			endd[i]+=f[j]*sq(r[j]-i);
		}
	}
	memset(mic,-1,sizeof(mic));
	long long ans=4e18;
	for (int i=0;i<256;i++) {
		ans=min(ans,dp(i,k)+endd[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
