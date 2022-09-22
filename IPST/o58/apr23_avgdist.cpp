#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int to,wgt;
};

int grp[50100];
vector<edge> pth[50100];

bool marked[50100];
bool visit[50100];
int subsize[50100];
int n;

void dfs(int x,int p) {
	n++;
	subsize[x]=1;
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		if (marked[i.to]) continue;
		dfs(i.to,x);
		subsize[x]+=subsize[i.to];
	}
}

int getCentroid(int x,int p) {	
	int mxChd=n-subsize[x];
	int heavyChd=-1;
	int heavySz=0;
	for (auto &i:pth[x]) {
		if (marked[i.to]) continue;
		if (i.to==p) continue;
		if (subsize[i.to]>heavySz) {
			heavySz=subsize[i.to];
			heavyChd=i.to;
		}
		mxChd=max(mxChd,subsize[i.to]);
	}
	if (mxChd<=n/2) return x;
	return getCentroid(heavyChd,x);
}

struct node {
	long long tothis[11];
	long long topar[11];
	int cnt[11];
	vector<int> chd;
	//int joint;
	int par;
	int grp;

	node() {
		par=0;
		grp=0;
		for (int i=0;i<11;i++) {
			topar[i]=0;
			cnt[i]=0;
			tothis[i]=0;
		}
	}
};

node tree[50100];

int buildTree(int x,int p) {
	n=0;
	dfs(x,p);
	int cen = getCentroid(x,p);
	marked[cen]=true;
	
	for (auto &i:pth[cen]) {
		if (marked[i.to]) continue;
		int sub=buildTree(i.to,cen);
		tree[cen].chd.push_back(sub);
		tree[sub].par=cen;
		//tree[sub].joint=i.to;
	}
	return cen;
}

int par[20][50100];
long long wgt[20][50100];
int dep[50100];

void predfs(int x,int p,int d) {
	dep[x]=d;
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		par[0][i.to]=x;
		wgt[0][i.to]=i.wgt;
		predfs(i.to,x,d+1);
	}
}

long long lca(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	long long ans=0;
	for (int i=0;i<20;i++) {
		if (dif&(1<<i)) {
			ans+=wgt[i][a];
			a=par[i][a];
		}
	}
	if (a==b) return ans;
	for (int i=19;i>=0;i--) {
		if (par[i][a]!=par[i][b]) {
			ans+=wgt[i][a];
			ans+=wgt[i][b];
			a=par[i][a];
			b=par[i][b];
		}
	}
	ans+=wgt[0][a];
	ans+=wgt[0][b];
	return ans;
}

long long sum[11];
int cnt[11];

void add(int cur,int x,int g,int chd,long long chg) {
	tree[cur].cnt[g]++;
	long long dis=lca(cur,x);
	long long tmp=lca(tree[cur].par,x);
	tree[cur].topar[g]+=tmp;
	tree[cur].tothis[g]+=chg;

	sum[g]+=(tree[cur].tothis[g]-tree[chd].topar[g]);
	sum[g]+=(dis*(tree[cur].cnt[g]-tree[chd].cnt[g]));

	//for (auto i:tree[cur].chd) {
		//if (i==chd) continue;
		//sum[g]+=tree[i].topar[g]+(dis*tree[i].cnt[g]);
	//}
	//if (tree[cur].grp==g) sum[g]+=dis;
	if (tree[cur].par) add(tree[cur].par,x,g,cur,tmp);
}

void rem(int cur,int x,int g,int chd,long long chg) {
	tree[cur].cnt[g]--;
	long long dis=lca(cur,x);
	long long tmp=lca(tree[cur].par,x);
	tree[cur].topar[g]-=tmp;
	tree[cur].tothis[g]-=chg;

	sum[g]-=(tree[cur].tothis[g]-tree[chd].topar[g]);
	sum[g]-=(dis*(tree[cur].cnt[g]-tree[chd].cnt[g]));

	//for (auto i:tree[cur].chd) {
		//if (i==chd) continue;
		//sum[g]-=tree[i].topar[g]+(dis*tree[i].cnt[g]);
	//}
	//if (tree[cur].grp==g) sum[g]-=dis;
	if (tree[cur].par) rem(tree[cur].par,x,g,cur,tmp);
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);	
	for (int i=1;i<=n;i++) {
		scanf("%d",&grp[i]);
	}
	int a,b,c;
	for (int i=1;i<n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
		pth[b].push_back(edge{a,c});
	}
	buildTree(1,1);
	par[0][1]=1;
	wgt[0][1]=0;
	predfs(1,1,0);
	for (int i=1;i<20;i++) {
		for (int j=0;j<=n;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
			wgt[i][j]=wgt[i-1][j]+wgt[i-1][par[i-1][j]];
		}
	}
	for (int i=1;i<=n;i++) {
		cnt[grp[i]]++;
		tree[i].grp=grp[i];
		add(i,i,grp[i],0,0);
		//printf("--> %d %lld\n",grp[i],sum[grp[i]]);
	}

	//for (int i=1;i<=n;i++) {
		//printf("%d %d %lld %d\n",i,tree[i].par,tree[i].topar[1],tree[i].cnt[1]);
	//}

	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++) {
		scanf("%d",&a);
		if (a==1) {
			scanf("%d",&b);
			if (cnt[b]==0) {
				printf("-1\n");
			} else if (cnt[b]==1) {
				printf("0\n");
			} else {
				printf("%f\n",(double)sum[b]*2/cnt[b]/(cnt[b]-1));
			}
		} else {
			scanf("%d%d",&b,&c);
			cnt[grp[b]]--;
			tree[b].grp=0;
			rem(b,b,grp[b],0,0);

			grp[b]=c;
			cnt[grp[b]]++;
			tree[b].grp=c;
			add(b,b,grp[b],0,0);
		}	
	}
	return 0;
}
