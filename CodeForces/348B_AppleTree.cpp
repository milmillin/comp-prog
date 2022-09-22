#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

int app[100100];
long long wgt[100100];
vector<int> pth[100100];
vector<int> rePth[100100];
bool visit[100100];
long long inc[100100];

long long gcd(long long a, long long b) {
	if (a%b==0) return b;
	return gcd(b,a%b);
}

long long lcm(long long a, long long b) {
	return a*b/gcd(a,b);
}

void dfs(int idx) {
	visit[idx]=true;
	for (int i=0;i<pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		dfs(pth[idx][i]);
		rePth[idx].push_back(pth[idx][i]);
	}
}

long long sum[100100];
long long rmd[100100];
long long appSum[100100];
long long minn[100100];

long long cut(int idx) {
	sum[idx]=0;
	for (int i=0;i<rePth[idx].size();i++) {
		sum[idx]+=cut(rePth[idx][i]);
	}
	rmd[idx]=1;
	appSum[idx]=0;
	minn[idx]=2e9;
	for (int i=0;i<rePth[idx].size();i++) {
		appSum[idx]+=wgt[rePth[idx][i]];
		rmd[idx]=lcm(rmd[idx],inc[rePth[idx][i]]);
		minn[idx]=min(minn[idx],wgt[rePth[idx][i]]);
	}
	if (rmd[idx]==0) {
		printf("Whoa");
		exit(0);
	}
	if (minn[idx]!=2e9) {
		//rmd*=rePth[idx].size();
		long long rmv=appSum[idx]-minn[idx]/rmd[idx]*rmd[idx]*rePth[idx].size();
		sum[idx]+=rmv;
		wgt[idx]=minn[idx]/rmd[idx]*rmd[idx]*rePth[idx].size();
		inc[idx]=rmd[idx]*rePth[idx].size();
	} else {
		wgt[idx]=app[idx];
	}
	//printf("%d %I64d %I64d %I64d %I64d\n",idx,sum,wgt[idx],inc[idx],minn);
	return sum[idx];
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&app[i]);
		inc[i]=1;
	}
	int a,b;
	for (int i=0;i<n-1;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	dfs(1);
	//if (n>=100000) return 0;
	printf("%I64d\n",cut(1));
	/*
	for (int i=1;i<=n;i++) {
		printf("%d ",wgt[i]);
	}
	printf("\n");
	*/
	return 0;
}
