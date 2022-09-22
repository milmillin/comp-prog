#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int to,wgt;
};

const int inf=0x3f3f3f3f;

struct node {
	int maxL,maxR,opt;
	
	node(int _maxL=-inf,int _maxR=-inf,int _opt=-inf):maxL(_maxL),maxR(_maxR),opt(_opt) {}
};

struct Rint {
	bool operator() (const int &l, const int &r) {
		return l>r;
	}
};
multiset<int,Rint> ch[100100],ans;

node segs[400100];
int lft[400100];
int rgt[400100];

vector<edge> pth[100100];
int par[100100];
int subsize[100100];
int wgtToPar[100100];

void dfs(int x,int p) {
	subsize[x]=1;
	par[x]=p;
	for (auto &e:pth[x]) {
		if (e.to==p) continue;
		wgtToPar[e.to]=e.wgt;
		dfs(e.to,x);
		subsize[x]+=subsize[e.to];
	}	
}

int idOf[100100];
int timeOf[100100];
int chnOf[100100];
int chnSzOf[100100];

int curTime=0;

void hld(int x,int chn) {
	idOf[curTime]=x;
	timeOf[x]=curTime++;
	chnOf[x]=chn;
	chnSzOf[chn]++;
	
	int mx=0,mxId=-1;
	for (auto &e:pth[x]) {
		if (e.to==par[x]) continue;
		if (subsize[e.to]>mx) {
			mx=subsize[e.to];
			mxId=e.to;
		}
	}	
	if (mx==0) return;
	hld(mxId,chn);
	for (auto &e:pth[x]) {
		if (e.to==par[x]) continue;
		if (e.to==mxId) continue;
		hld(e.to,e.to);
	}
}

int sum[100100];

int segCnt=0;
int root[100100];

bool color[100100];

void maintain(int pos,int id) {
	//d1 and d2 are two max distance from id
	int d1=-inf;
	int d2=-inf;
	//if it is white, set to zero
	if (color[id]==0) d1=d2=0;	
	//get two max dist
	if (ch[id].size()) d1=max(d1,*(ch[id].begin()));
	if (ch[id].size()>1) d2=max(d2,*(++ch[id].begin()));
	//set value in segs
	segs[pos].maxL=segs[pos].maxR=d1;
	segs[pos].opt=d1+d2;

	if (color[id]==0) segs[pos].opt=max(segs[pos].opt,0);
}

node merge(const node &l, const node &r,int dL,int dMid,int dR) {
	node tmp;
	tmp.maxL=max(l.maxL,dL+r.maxL);
	tmp.maxR=max(r.maxR,dR+l.maxR);
	tmp.opt=max(max(l.opt,r.opt),l.maxR+dMid+r.maxL);
	return tmp;
}

void build(int x,int l,int r) {
	if (l+1==r) {
		int u=idOf[l];
		for (auto &e:pth[u]) {
			if (e.to==par[u]) continue;
			if (chnOf[e.to]==chnOf[u]) continue;
			build(root[e.to]=segCnt++,timeOf[e.to],timeOf[e.to]+chnSzOf[e.to]);
			ch[u].insert(segs[root[e.to]].maxL+e.wgt);
			ans.insert(segs[root[e.to]].opt);
		}
		maintain(x,u);
	} else {
		int mid=(l+r)>>1;
		build(lft[x]=segCnt++,l,mid);
		build(rgt[x]=segCnt++,mid,r);
		segs[x]=merge(segs[lft[x]],segs[rgt[x]],sum[mid]-sum[l],sum[mid]-sum[mid-1],sum[r-1]-sum[mid-1]);
	}
}

vector<int> path;
void findPath(int x) {
	while (x) {
		path.push_back(x);
		x=par[chnOf[x]];
	}
}

void modify(int x,int l,int r,int idx) {
	assert(chnOf[path[idx]]==chnOf[idOf[l]]);
	if (l+1==r) {
		int u=idOf[l];
		if (idx+1!=(int)path.size()) {
			int nxt=chnOf[path[idx+1]];
			ans.erase(ans.find(segs[root[nxt]].opt));
			ch[u].erase(ch[u].find(segs[root[nxt]].maxL+wgtToPar[nxt]));
			modify(root[nxt],timeOf[nxt],timeOf[nxt]+chnSzOf[nxt],idx+1);
			ans.insert(segs[root[nxt]].opt);
			ch[u].insert(segs[root[nxt]].maxL+wgtToPar[nxt]);
		}
		maintain(x,u);	
	} else {
		int u=path[idx];
		int mid=(l+r)>>1;
		if (timeOf[u]<mid) modify(lft[x],l,mid,idx);
		else modify(rgt[x],mid,r,idx);
		segs[x]=merge(segs[lft[x]],segs[rgt[x]],sum[mid]-sum[l],sum[mid]-sum[mid-1],sum[r-1]-sum[mid-1]);
	}
}

int whiteCnt;

int main () {
	int n;
	scanf("%d",&n);

	memset(color,0,sizeof(color));
	whiteCnt=n;

	
	int a,b,c;
	for (int i=1;i<n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
		pth[b].push_back(edge{a,c});
	}
	
	dfs(1,0);
	hld(1,1);

	for (int i=0;i<n;i++) {
		sum[i]=wgtToPar[idOf[i]];
		if (i) sum[i]+=sum[i-1];
	}
	build(root[1]=segCnt++,timeOf[1],timeOf[1]+chnSzOf[1]);
	int q;
	scanf("%d",&q);
	char op[2];
	while (q--) {
		scanf("%s",op);
		if (op[0]=='C') {
			scanf("%d",&a);
			if (color[a]) whiteCnt++;
			else whiteCnt--;
			color[a]=!color[a];	
			path.clear();
			findPath(a);
			reverse(path.begin(),path.end());
			modify(root[1],timeOf[1],timeOf[1]+chnSzOf[1],0);
		} else if (op[0]=='A') {
			if (whiteCnt==0) {
				printf("They have disappeared.\n");
			} else {
				printf("%d\n",max(*ans.begin(),segs[0].opt));
			}
		} else {
			assert(false);
		}
	}
	
	return 0;
}
