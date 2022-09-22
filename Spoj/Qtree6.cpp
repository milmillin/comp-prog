#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[100100];
int subsize[100100];
int par[100100];

void dfs(int x,int p) {
	par[x]=p;
	subsize[x]=1;
	for (auto i:pth[x]) {
		if (i==p) continue;
		dfs(i,x);
		subsize[x]+=subsize[i];
	}
}

int timeOf[100100];
int idOf[100100];
int chnOf[100100];
int szOf[100100];
int curTime=0;

void hld(int x,int chn) {
	chnOf[x]=chn;
	szOf[chn]++;
	idOf[curTime]=x;
	timeOf[x]=curTime++;

	int mx=0;
	int mxId=-1;
	for (auto i:pth[x]) {
		if (i==par[x]) continue;
		if (subsize[i]>mx) {
			mx=subsize[i];
			mxId=i;
		}
	}
	if (!mx) return;
	hld(mxId,chn);
	for (auto i:pth[x]) {
		if (i==par[x]) continue;
		if (i==mxId) continue;
		hld(i,i);
	}
}

struct node {
	int l0,l1,r0,r1;
	int sum0,sum1,sz;
	node(int _l0=0,int _l1=0,int _r0=0,int _r1=0,int _sum0=0,int _sum1=0,int _sz=0):l0(_l0),l1(_l1),r0(_r0),r1(_r1),sum0(_sum0),sum1(_sum1),sz(_sz) {}
};

node segs[300100];
int lft[300100];
int rgt[300100];

int root[100100];
int segCnt=0;

node merge(const node &a, const node &b) {
	node tmp; 
	tmp.l0=a.l0;
	if (a.sum0==a.sz) tmp.l0=a.l0+b.l0;
	tmp.l1=a.l1;
	if (a.sum1==a.sz) tmp.l1=a.l1+b.l1;
	tmp.r0=b.r0;
	if (b.sum0==b.sz) tmp.r0=b.r0+a.r0;
	tmp.r1=b.r1;
	if (b.sum1==b.sz) tmp.r1=b.r1+a.r1;

	tmp.sum0=a.sum0+b.sum0;
	tmp.sum1=a.sum1+b.sum1;
	tmp.sz=a.sz+b.sz;	

	return tmp;
}

int ch0[100100];
int ch1[100100];

int color[100100];

void put(int pos,int id) {
	node& cur=segs[pos];
	cur.sz=1;

	if (color[id]==0) {
		cur.sum0=1;
		cur.sum1=0;
		cur.l0=cur.r0=1+ch0[id];
		cur.l1=cur.r1=0;
	} else {
		cur.sum0=0;
		cur.sum1=1;
		cur.l0=cur.r0=0;
		cur.l1=cur.r1=1+ch1[id];
	}
}

void build(int pos,int l,int r) {
	if (l+1==r) {
		int u=idOf[l];
		for (auto i:pth[u]) {
			if (i==par[u]) continue;
			if (chnOf[i]==chnOf[u]) continue;
			build(root[i]=segCnt++,timeOf[i],timeOf[i]+szOf[i]);
			ch0[u]+=segs[root[i]].l0;
			ch1[u]+=segs[root[i]].l1;
		}
		put(pos,u);
	} else {
		int m=(l+r)>>1;
		build(lft[pos]=segCnt++,l,m);
		build(rgt[pos]=segCnt++,m,r);
		segs[pos]=merge(segs[lft[pos]],segs[rgt[pos]]);
	}
}

vector<int> path;
void findPath(int id) {
	path.clear();
	while (id) {
		path.push_back(id);
		id=par[chnOf[id]];
	}
	reverse(path.begin(),path.end());
}

void modify(int pos,int l,int r,int idx) {
	if (l+1==r) {
		int u=idOf[l];
		if (idx+1!=path.size()) {
			int i=chnOf[path[idx+1]];
			ch0[u]-=segs[root[i]].l0;
			ch1[u]-=segs[root[i]].l1;
			modify(root[i],timeOf[i],timeOf[i]+szOf[i],idx+1);
			ch0[u]+=segs[root[i]].l0;
			ch1[u]+=segs[root[i]].l1;
		}
		put(pos,u);
	} else {
		int m=(l+r)>>1;
		if (timeOf[path[idx]]<m) modify(lft[pos],l,m,idx);
		else modify(rgt[pos],m,r,idx);
		segs[pos]=merge(segs[lft[pos]],segs[rgt[pos]]);
	}
}

node querySeg(int pos,int l,int r,int ll,int rr) {
	if (rr<=l||ll>=r) return node();
	if (ll<=l&&rr>=r) return segs[pos];
	int m=(l+r)>>1;
	return merge(querySeg(lft[pos],l,m,ll,rr),querySeg(rgt[pos],m,r,ll,rr));
}

int query(int id) {
	int col=color[id];
	int ans=0;
	while (id) {
		int chn=chnOf[id];
		node l=querySeg(root[chn],timeOf[chn],timeOf[chn]+szOf[chn],timeOf[chn],timeOf[id]);
		node r=querySeg(root[chn],timeOf[chn],timeOf[chn]+szOf[chn],timeOf[id],timeOf[chn]+szOf[chn]);
		if (col==0) {
			ans=l.r0+r.l0;
			if (l.sum0!=l.sz) return ans;
		} else {
			ans=l.r1+r.l1;
			if (l.sum1!=l.sz) return ans;
		}
		if (color[par[chnOf[id]]]!=col) return ans;
		id=par[chnOf[id]];
	}
	return ans;
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
	
	int q;
	scanf("%d",&q);
	while (q--) {
		scanf("%d%d",&a,&b);
		if (a==0) {
			printf("%d\n",query(b));
		} else {
			color[b]=!color[b];
			findPath(b);
			modify(root[1],timeOf[1],timeOf[1]+szOf[1],0);
		}
	}

	return 0;
}
