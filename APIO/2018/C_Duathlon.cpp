#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

vector<int> pth[100100];

int di[100100];
int lo[100100];
bool visit[100100];
bool isArt[100100];
int ti;
vector<int> stk;
vector<int> comp[300100];
int cnum=0;

vector<int> pthbc[100100];
int nbc;
int id[100100];
int sz[300100];
int szwoart[300100];

int subsize[300100]; //woart

int st;

void dfs(int x,int p) {
	di[x]=lo[x]=ti++;
	visit[x]=true;
	stk.push_back(x);
	for (auto i:pth[x]) {
		if (i==p) continue;
		if (visit[i]) {
			lo[x]=min(lo[x],di[i]);
			continue;
		}
		dfs(i,x);
		if (lo[i]>=di[x]) {
			isArt[x]=di[x]>0||di[i]>1;	
			comp[cnum].push_back(x);
			while (comp[cnum].back()!=i) {
				comp[cnum].push_back(stk.back());
				stk.pop_back();
			}
			cnum++;
		}
		lo[x]=min(lo[x],lo[i]);
	}
}

long long ans=0;
int n,m;

int nn;
bool vis[100100];
void predfs(int x,int p) {
	subsize[x]=szwoart[x];
	//nn++;
	vis[x]=true;
	for (auto i:pthbc[x]) {
		if (i==p) continue;
		predfs(i,x);
		subsize[x]+=subsize[i];
	}	
}

void dfs2(int x,int p) {
	int tot=0;
	for (auto i:pthbc[x]) {
		if (i==p) continue;
		dfs2(i,x);
		tot+=subsize[i];
	}
	int hi=nn-subsize[x];
	tot+=hi;

	//printf("zz %d %lld\n",x,ans);
	if (sz[x]==1) {
		//art
		for (auto i:pthbc[x]) {
			if (i==p) continue;
			ans+=(long long)(subsize[i])*(tot-subsize[i]);
		}
		ans+=(long long)hi*(tot-hi);
	} else {
		for (auto i:pthbc[x]) {
			if (i==p) continue;
			//start at sub[i]
			if (sz[x]>=2) ans+=(long long)(subsize[i])*(sz[x]-2)*(tot-subsize[i]); //ends at other sub
			if (sz[x]>2) {
				//ends in x
				if (subsize[i]>0) ans+=(long long)(subsize[i]-1)*(sz[x]-1)*(long long)(sz[x]-2)*2;
				//start in x ends at other
				//ans+=(long long)(sz[x]-2)*(subsize[i]); //ends at other	
				//printf("yay %d\n",subsize[i]);
			}
		}
		if (sz[x]>=2) ans+=(long long)(hi)*(sz[x]-2)*(tot-hi);
		//printf("ss %d\n",sz[x]);
		if (sz[x]>2) {
			//start in x ends in x;
			//printf("yay\n");
			ans+=(long long)(sz[x])*(sz[x]-1)*(sz[x]-2);

			//covering hi
			if (hi>0) ans+=(long long)(hi-1)*(sz[x]-1)*(long long)(sz[x]-2)*2;
			//ans+=(long long)hi*(sz[x]-2);	
		}
	}
	//printf("-- %d %lld\n",x,ans);
						
	
}

int main () {
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}	
	st=0;
	for (int i=1;i<=n;i++) {
		if (visit[i]) continue;
		stk.clear();
		ti=0;
		dfs(i,i);
	}
	for (int i=1;i<=n;i++) {
		if (!isArt[i]) continue;
		id[i]=nbc++;
		sz[id[i]]=szwoart[id[i]]=1;
	}
	for (int i=0;i<cnum;i++) {
		for (auto j:comp[i]) {
			if (isArt[j]) {
				pthbc[id[j]].push_back(nbc);
				pthbc[nbc].push_back(id[j]);
				sz[nbc]++;
			} else {
				id[j]=nbc;
				sz[nbc]++;
				szwoart[nbc]++;
			}
		}
		nbc++;
	}
	//printf("--%d\n",n);
	//for (int i=1;i<=n;i++) {
		//printf("%d ",id[i]);
	//}
	//printf("\n");
	//for (int i=0;i<nbc;i++) {
		//printf("%d ",szwoart[i]);
	//}
	//printf("\n");
	//dfs2(0,0);
	for (int i=0;i<nbc;i++) {
		if (vis[i]) continue;
		//nn=0;
		predfs(i,i);
		nn=subsize[i];
		//printf("--%d\n",nn);
		dfs2(i,i);
	}
	printf("%lld\n",ans);
	return 0;
}
