#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[100100];
int subsize[100100];
int par[100100];

void init(int x,int p) {
	subsize[x]=1;
	par[x]=p;
	for (auto &i:pth[x]) {
		if (i==p) continue;
		init(i,x);
		subsize[x]+=subsize[i];
	}	
}

int chainOf[100100];
int headOf[100100];
int tailOf[100100];
int posInSeg[100100];

int curChain;
int curPos;

void hld (int x,int p) {
	if (headOf[curChain]==0) {
		headOf[curChain]=x;
	}
	tailOf[curChain]=x;
	chainOf[x]=curChain;
	posInSeg[x]=curPos++;
	
	int mx=0;
	int mxId=-1;
	for (auto &i:pth[x]) {
		if (i==p) continue;
		if (subsize[i]>mx) {
			mx=subsize[i];
			mxId=i;
		}
	}

	if (mxId!=-1) {
		hld(mxId,x);
	}

	for (auto &i:pth[x]) {
		if (i==p) continue;
		if (i==mxId) continue;
		curChain++;
		hld(i,x);
	}
}

int seg[400100];
const int inf=0x3f3f3f3f;

int querySeg(int x,int l,int r,int ll,int rr) {
	if (rr<=l||ll>=r) return inf;
	if (ll<=l&&rr>=r) return seg[x];
	int m=(l+r)>>1;
	int left=querySeg(x*2+1,l,m,ll,rr);
	if (left!=inf) return left;
	return querySeg(x*2+2,m,r,ll,rr);
}

void updateSeg(int x,int l,int r,int k,int val) {
	if (k<l||k>=r) return;
	if (l+1==r) {
		seg[x]=val;
		return;
	}
	int m=(l+r)>>1;
	updateSeg(x*2+1,l,m,k,val);
	updateSeg(x*2+2,m,r,k,val);
	if (seg[x*2+1]!=inf) seg[x]=seg[x*2+1];
	else seg[x]=seg[x*2+2];
}

int query(int x) {
	int cur=x;
	int curAns=inf;
	while (true) {
		int res=querySeg(0,0,curPos,posInSeg[headOf[chainOf[x]]],posInSeg[x]+1);
		if (res!=inf) curAns=res;
		if (chainOf[cur]==chainOf[1]) break;
		cur=par[headOf[chainOf[x]]];
	}
	return curAns;
}

void update(int x,int val) {
	int cur=x;
	int curVal=val;
	while (true) {
		updateSeg(0,0,curPos,posInSeg[cur],curVal);
		if (chainOf[cur]==chainOf[1]) break;
		curVal=querySeg(0,0,curPos,posInSeg[headOf[chainOf[x]]],posInSeg[tailOf[chainOf[x]]]+1);
		cur=par[headOf[chainOf[x]]];
	}
}

bool color[100100];

int main () {
	int n;
	int q;
	scanf("%d%d",&n,&q);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	init(1,1);
	hld(1,1);
	
	memset(seg,0x3f,sizeof(seg));

	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		if (a==0) {
			color[b]=!color[b];
			update(b,(color[b])?b:inf);
		} else {
			int res=query(b);
			printf("%d\n",(res==inf)?-1:res);
		}
	}

	return 0;
}
