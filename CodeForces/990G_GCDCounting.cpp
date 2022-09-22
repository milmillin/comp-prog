#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

int tbl[200100];
vector<int> pth[200100];
bool del[200100];
int subsize[200100];
int sz;

void dfs(int x,int p) {
	subsize[x]=1;
	for (auto i:pth[x]) {
		if (del[i]) continue;
		if (i==p) continue;
		dfs(i,x);
		subsize[x]+=subsize[i];
	}
}

int findcen(int x,int p) {
	for (auto i:pth[x]) {
		if (del[i]) continue;
		if (i==p) continue;
		if (subsize[i]>sz/2) return findcen(i,x);
	}	
	return x;
}

int gcd(int a,int b) {
	if (!b) return a;
	return gcd(b,a%b);
}

long long ans[200100];

long long cnt[200100];
long long newcnt[200100];
set<int> avail;
set<int> newavail;

void solve(int x,int p,int g) {
	for (auto i:avail) {
		ans[gcd(g,i)]+=cnt[i];
	}
	newcnt[g]++;
	newavail.insert(g);	
	for (auto i:pth[x]) {
		if (del[i]) continue;
		if (i==p) continue;
		solve(i,x,gcd(g,tbl[i]));
	}
}

int decom(int x) {
	//printf("%d\n",x);
	dfs(x,x);
	sz=subsize[x];
	int cen=findcen(x,x);
	del[cen]=true;
	//printf("-- %d\n",cen);
	ans[tbl[cen]]++;
	cnt[tbl[cen]]++;
	avail.insert(tbl[cen]);

	for (auto i:pth[cen]) {
		if (del[i]) continue;
		solve(i,cen,gcd(tbl[i],tbl[cen]));
		for (auto j:newavail) {
			cnt[j]+=newcnt[j];
			newcnt[j]=0;
			avail.insert(j);
		}
		newavail.clear();
	}

	for (auto i:avail) {
		cnt[i]=0;
	}
	avail.clear();

	for (auto i:pth[cen]) {
		if (del[i]) continue;
		decom(i);
	}
	return cen;
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	int a,b;
	for (int i=0;i<n-1;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	//printf("yay\n");
	decom(1);
	for (int i=1;i<=200000;i++) {
		if (ans[i]) {
			printf("%d %lld\n",i,ans[i]);
		}
	}
	return 0;
}
