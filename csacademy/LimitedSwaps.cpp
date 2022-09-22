#include <cstdio>
#include <algorithm>

using namespace std;

int cnt[300100];
int mx[300100];
int mxId[300100];
int tbl[100100];

void build(int idx,int l,int r) {
	if (l+1==r) {
		mx[idx]=tbl[l];
		mxId[idx]=l;
		cnt[idx]=1;
		return;
	}
	int m=(l+r)>>1;
	build(idx*2+1,l,m);
	build(idx*2+2,m,r);
	cnt[idx]=cnt[idx*2+1]+cnt[idx*2+2];
	if (mx[idx*2+1]>mx[idx*2+2]) {
		mx[idx]=mx[idx*2+1];
		mxId[idx]=mxId[idx*2+1];
	} else if (mx[idx*2+2]>mx[idx*2+1]) {
		mx[idx]=mx[idx*2+2];
		mxId[idx]=mxId[idx*2+2];
	} else {
		mx[idx]=mx[idx*2+1];
		if (mxId[idx*2+1]>mxId[idx*2+2]) {
			mxId[idx]=mxId[idx*2+2];
		} else {
			mxId[idx]=mxId[idx*2+1];
		}
	}
}

pair<int,int> query(int idx,int l,int r, long long k) {
	//printf("%d %d %d %lld\n",idx,l,r,k);
	if (l+1==r) {
		return {mx[idx],mxId[idx]};
	}
	int m=(l+r)>>1;
	if (k<=cnt[idx*2+1]) return query(idx*2+1,l,m,k);
	else {
		pair<int,int> tmp=query(idx*2+2,m,r,k-cnt[idx*2+1]);
		if (tmp.first<mx[idx*2+1]) {
			return {mx[idx*2+1],mxId[idx*2+1]};
		} else if (mx[idx*2+1]<tmp.first) {
			return tmp;
		} else {
			if (tmp.second<mxId[idx*2+1]) {
				return tmp;
			} else {
				return {mx[idx*2+1],mxId[idx*2+1]};
			}
		}
	}
}

int ask(int idx,int l,int r,int k) {
	if (l+1==r) {
		cnt[idx]=0;
		mx[idx]=-1;
		mxId[idx]=-1;
		return 1;
	}
	int m=(l+r)>>1;
	int ans;
	if (k<m) ans=ask(idx*2+1,l,m,k);
	else ans=cnt[idx*2+1]+ask(idx*2+2,m,r,k);

	cnt[idx]=cnt[idx*2+1]+cnt[idx*2+2];
	if (mx[idx*2+1]>mx[idx*2+2]) {
		mx[idx]=mx[idx*2+1];
		mxId[idx]=mxId[idx*2+1];
	} else if (mx[idx*2+2]>mx[idx*2+1]) {
		mx[idx]=mx[idx*2+2];
		mxId[idx]=mxId[idx*2+2];
	} else {
		mx[idx]=mx[idx*2+1];
		if (mxId[idx*2+1]>mxId[idx*2+2]) {
			mxId[idx]=mxId[idx*2+2];
		} else {
			mxId[idx]=mxId[idx*2+1];
		}
	}
	return ans;
}

int main () {
	int n;
	long long k;
	scanf("%d%lld",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	build(0,0,n);
	
	pair<int,int> tmp;
	int tmp2;
	for (int i=0;i<n;i++) {
		tmp=query(0,0,n,k+1);
		printf("%d ",tmp.first);
		tmp2=ask(0,0,n,tmp.second);
		//printf("%d %d\n",tmp.second,tmp2-1);
		k-=tmp2-1;
	}
	printf("\n");
	return 0;
}
