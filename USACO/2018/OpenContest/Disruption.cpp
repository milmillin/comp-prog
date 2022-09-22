#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int to,id;
};

vector<edge> pth[50010];
int subsize[50010];
int par[20][50010];
int edgeId[50010];
int dep[50010];

void init(int x,int p) {
	subsize[x]=1;
	dep[x]=dep[p]+1;
	par[0][x]=p;
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		edgeId[i.to]=i.id;
		init(i.to,x);
		subsize[x]+=subsize[i.to];
	}
}

int lca (int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	for (int i=0;i<20;i++) {
		if ((1<<i)&dif) a=par[i][a];
	}
	if (a==b) return a;
	for (int i=19;i>=0;i--) {
		if (par[i][a]!=par[i][b]) {
			a=par[i][a];
			b=par[i][b];
		}
	}
	return par[0][a];
}

int chainHead[50010];
int chainOf[50010];
int posInSegOf[50010];

int chainNo=0;
int curPos=0;

void hld(int x,int p) {
	if (chainHead[chainNo]==-1) chainHead[chainNo]=x;
	chainOf[x]=chainNo;	
	posInSegOf[x]=curPos++;

	//find heavy child
	int mx=0,id=-1;
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		if (subsize[i.to]>mx) {
			mx=subsize[i.to];
			id=i.to;
		}
	}

	if (id!=-1) {
		hld(id,x);
	}

	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		if (i.to==id) continue;
		chainNo++;
		hld(i.to,x);
	}
}

int seg[200100];

void setSeg(int x,int l,int r,int ll,int rr,int k) {
	if (ll>=r||rr<=l) return;
	if (ll<=l&&rr>=r) {
		seg[x]=min(seg[x],k);
		return;
	}
	int m=(l+r)>>1;
	setSeg(x*2+1,l,m,ll,rr,k);
	setSeg(x*2+2,m,r,ll,rr,k);
}

int query(int x,int l,int r,int k) {
	if (k<l||k>=r) return 1e9;
	if (l+1==r) return seg[x];
	int m=(l+r)>>1;
	return min(seg[x],min(query(x*2+1,l,m,k),query(x*2+2,m,r,k)));
}

void setWhole(int a,int b,int k) {
	int cur=b;
	while (chainOf[cur]!=chainOf[a]) {
		setSeg(0,0,curPos,posInSegOf[chainHead[chainOf[cur]]],posInSegOf[cur]+1,k);
		//printf("set %d %d\n",posInSegOf[chainHead[chainOf[cur]]],posInSegOf[cur]);
		cur=par[0][chainHead[chainOf[cur]]];
	}
	setSeg(0,0,curPos,posInSegOf[a]+1,posInSegOf[cur]+1,k);
	//printf("sett %d %d\n",posInSegOf[a]+1,posInSegOf[cur]);
}

int ans[50010];

int main () {
	freopen("disrupt.in","r",stdin);
	freopen("disrupt.out","w",stdout);
	int n,m;	
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<n-1;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back({b,i});
		pth[b].push_back({a,i});
	}
	init(1,1);
	fill(chainHead,chainHead+n,-1);	
	hld(1,1);
	fill(seg,seg+200000,1e9);
	for (int i=1;i<20;i++) {
		for (int j=1;j<=n;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
		}
	}
	int cost;
	int c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&cost);
		c=lca(a,b);
		//printf("lca %d\n",c);
		setWhole(c,a,cost);
		setWhole(c,b,cost);	
	}

	for (int i=2;i<=n;i++) {
		ans[edgeId[i]]=query(0,0,curPos,posInSegOf[i]);
	}
	for (int i=0;i<n-1;i++) {
		printf("%d\n",(ans[i]==1e9)?-1:ans[i]);
	}
	return 0;
}
