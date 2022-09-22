#include <cstdio>
#include <algorithm>

using namespace std;

int pfx[300100];
int sfx[300100];
int sum[300100];
int mxx[300100];
int tbl[100100];

void build(int idx,int l,int r) {
	if (l+1==r) {
		mxx[idx]=sum[idx]=pfx[idx]=sfx[idx]=tbl[l];
		return;
	}

	int m=(l+r)>>1;
	build(idx*2+1,l,m);
	build(idx*2+2,m,r);
	
	pfx[idx]=max(pfx[idx*2+1],sum[idx*2+1]+pfx[idx*2+2]);
	sfx[idx]=max(sfx[idx*2+2],sum[idx*2+2]+sfx[idx*2+1]);
	mxx[idx]=max(mxx[idx*2+1],max(mxx[idx*2+2],pfx[idx*2+2]+sfx[idx*2+1]));
	sum[idx]=sum[idx*2+1]+sum[idx*2+2];
	//printf("%d %d %d %d %d %d %d\n",idx,l,r,pfx[idx],sfx[idx],mxx[idx],sum[idx]);
	return;
}

void update(int idx,int l,int r,int k) {
	if (l+1==r) {
		mxx[idx]=sum[idx]=pfx[idx]=sfx[idx]=tbl[l];
		return;
	}
	int m=(l+r)>>1;
	if (k<m) update(idx*2+1,l,m,k);
	else update(idx*2+2,m,r,k);

	pfx[idx]=max(pfx[idx*2+1],sum[idx*2+1]+pfx[idx*2+2]);
	sfx[idx]=max(sfx[idx*2+2],sum[idx*2+2]+sfx[idx*2+1]);
	mxx[idx]=max(mxx[idx*2+1],max(mxx[idx*2+2],pfx[idx*2+2]+sfx[idx*2+1]));
	sum[idx]=sum[idx*2+1]+sum[idx*2+2];
	//printf("%d %d %d %d %d %d %d\n",idx,l,r,pfx[idx],sfx[idx],mxx[idx],sum[idx]);
	return;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	build(0,0,n);
	printf("%d\n",mxx[0]);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		tbl[a]=b;
		update(0,0,n,a);
		printf("%d\n",mxx[0]);
	}
	return 0;
}
