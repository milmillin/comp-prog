#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pth[100100];
int subsize[100100];
int par[100100];

void dfs(int x,int p) {
	subsize[x]=1;
	par[x]=p;
	for (auto i:pth[x]) {
		if (i==p) continue;
		dfs(i,x);
		subsize[x]+=subsize[i];
	}
}

int chnOf[100100];
int timeOf[100100];
int idOf[100100];
int szOf[100100];
int curTime=0;

void hld(int x,int chn) {
	chnOf[x]=chn;
	idOf[curTime]=x;
	timeOf[x]=curTime++;	
	szOf[chn]++;

	int mx=0;
	int mxId=-1;
	for (auto i:pth[x]) {
		if (i==par[x]) continue;
		if (subsize[i]>mx) {
			mx=subsize[i];
			mxId=i;
		}
	}

	if (mx==0) return;
	hld(mxId,chn);

	for (auto i:pth[x]) {
		if (i==par[x]) continue;
		if (i==mxId) continue;
		hld(i,i);
	}
}

const int inf=0x3f3f3f3f;

struct node {
	int minL;
	int minR;

	node(int _minL=inf,int _minR=inf): minL(_minL),minR(_minR) {}
};

node segs[300100];
int lft[300100];
int rgt[300100];
int segCnt=0;

multiset<int> ch[100100];
bool color[100100];

int root[100100];

void putSegs(int pos,int id,int ti) {
	int posL=ti-timeOf[chnOf[id]];	
	int posR=szOf[chnOf[id]]-posL-1; 

	int mn=inf;
	if (ch[id].size()) mn=min(mn,*(ch[id].begin()));
	if (color[id]) mn=min(mn,0);

	segs[pos].minL=posL+mn;
	segs[pos].minR=posR+mn;
}

node merge(const node &l, const node &r) {
	return node(min(l.minL,r.minL),min(l.minR,r.minR));
}

void build(int x,int l,int r) {
	if (l+1==r) {
		int u=idOf[l];
		for (auto i:pth[u]) {
			if (i==par[u]) continue;
			if (chnOf[i]==chnOf[u]) continue;
			build(root[i]=segCnt++,timeOf[i],timeOf[i]+szOf[i]);
			ch[u].insert(segs[root[i]].minL+1);	
		}
		putSegs(x,u,timeOf[u]);
	} else {
		int m=(l+r)>>1;
		build(lft[x]=segCnt++,l,m);
		build(rgt[x]=segCnt++,m,r);
		segs[x]=merge(segs[lft[x]],segs[rgt[x]]);
	}
}

vector<int> path;
void findpath(int id) {
	path.clear();
	while (id) {
		path.push_back(id);
		id=par[chnOf[id]];
	}
	reverse(path.begin(),path.end());
}

void modify(int x,int l,int r,int idx) {
	if (l+1==r) {
		int u=idOf[l];
		if (idx+1!=path.size()) {
			int nxt=chnOf[path[idx+1]];
			ch[u].erase(ch[u].find(segs[root[nxt]].minL+1));
			modify(root[nxt],timeOf[nxt],timeOf[nxt]+szOf[nxt],idx+1);
			ch[u].insert(segs[root[nxt]].minL+1);
		}
		putSegs(x,u,timeOf[u]);
	} else {
		int m=(l+r)>>1;
		if (timeOf[path[idx]]<m) modify(lft[x],l,m,idx);
		else modify(rgt[x],m,r,idx);
		segs[x]=merge(segs[lft[x]],segs[rgt[x]]);
	}
}

node query(int x,int l,int r,int ll,int rr) {
	if (ll>=r||rr<=l) return node();
	if (ll<=l&&rr>=r) return segs[x];
	int m=(l+r)>>1;
	return merge(query(lft[x],l,m,ll,rr),query(rgt[x],m,r,ll,rr));
}

int queryLine(int id) {
	int chn=chnOf[id];
	int mnL=query(root[chn],timeOf[chn],timeOf[chn]+szOf[chn],timeOf[chn],timeOf[id]).minR;
	int mnR=query(root[chn],timeOf[chn],timeOf[chn]+szOf[chn],timeOf[id],timeOf[chn]+szOf[chn]).minL;
	int posL=timeOf[id]-timeOf[chnOf[id]];	
	int posR=szOf[chnOf[id]]-posL-1; 

	return min(mnL-posR,mnR-posL);	
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}

	dfs(1,0);
	hld(1,1);

	build(root[1]=segCnt++,timeOf[1],timeOf[1]+szOf[1]);

	int whiteCnt=0;

	int q;
	scanf("%d",&q);
	while (q--) {
		scanf("%d%d",&a,&b);
		if (a==0) {
			if (color[b]) whiteCnt--;
			else whiteCnt++;
			color[b]=!color[b];

			findpath(b);

			modify(root[1],timeOf[1],timeOf[1]+szOf[1],0);	
		} else {
			if (whiteCnt==0) {
				printf("-1\n");
			} else {
				int ans=inf;
				int curAdd=0;
				while (b) {
					ans=min(ans,queryLine(b)+curAdd);
					curAdd+=timeOf[b]-timeOf[chnOf[b]]+1;
					b=par[chnOf[b]];
				}
				printf("%d\n",ans);
			}
		}
	}

	return 0;
}
