#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];
int qs[100100];
int seg[300100];
int mn[30010];
int add[300100];
int mxId[300100];
int mnId[300100];

void build(int idx,int l,int r) {
	if (l+1==r) {
		mn[idx]=seg[idx]=qs[l];
		mnId[idx]=mxId[idx]=idx;
		return;
	}
	int m=(l+r)>>1;
	build(idx*2,l,m);
	build(idx*2+1,m,r);
	if (seg[idx*2]>seg[idx*2+1]) {
		seg[idx]=seg[idx*2];
		mxId[idx]=mxId[idx*2];
	} else if (seg[idx*2]<seg[idx*2+1]) {
		seg[idx]=seg[idx*2+1];
		mxId[idx]=mxId[idx*2+1];
	} else {
		seg[idx]=seg[idx*2+1];
		mxId[idx]=min(mxId[idx*2],mxId[idx*2+1]);
	}
	//seg[idx]=max(seg[idx*2],seg[idx*2+1]);
	//m[idx]=min(mn[idx*2],mn[idx*2+1]);
	if (mn[idx*2]>mn[idx*2+1]) {
		mn[idx]=mn[idx*2+1];
		mnId[idx]=mnId[idx*2+1];
	} else if (mn[idx*2]<mn[idx*2+1]) {
		mn[idx]=mn[idx*2];
		mnId[idx]=mnId[idx*2];
	} else {
		mn[idx]=mn[idx*2];
		mnId[idx]=max(mnId[idx*2],mnId[idx*2+1]);
	}
}

int query(int idx,int l,int r,int ll,int rr,int &id) {
	if (ll>=r||rr<=l) return -2e9;
	if (ll<=l&&rr>=r) {
		id=mxId[idx];
		return seg[idx]+add[idx];
	}
	int m=(l+r)>>1;
	int i1,i2,tmp1,tmp2;
	tmp1=query(idx*2,l,m,ll,rr,i1);
	tmp2=query(idx*2+1,m,r,ll,rr,i2);
	if (tmp1>tmp2) {
		id=i1;
		return tmp1+add[idx];
	} else if (tmp1<tmp2) {
		id=i2;
		return tmp2+add[idx];
	} else {
		id=min(i1,i2);
		return tmp1+add[idx];
	}
	//return max(query(idx*2,l,m,ll,rr,id),query(idx*2+1,m,r,ll,rr,id))+add[idx];
}

int query_m(int idx,int l,int r,int ll,int rr,int &id) {
	if (ll>=r||rr<=l) return 2e9;
	if (ll<=l&&rr>=r) {
		id=mnId[idx];
		return mn[idx]+add[idx];
	}
	int m=(l+r)>>1;
	int i1,i2,tmp1,tmp2;
	tmp1=query_m(idx*2,l,m,ll,rr,i1);
	tmp2=query_m(idx*2+1,m,r,ll,rr,i2);
	if (tmp1<tmp2) {
		id=i1;
		return tmp1+add[idx];
	} else if (tmp1>tmp2) {
		id=i2;
		return tmp2+add[idx];
	} else {
		id=max(i1,i2);
		return tmp1+add[idx];
	}
	//return min(query_m(idx*2,l,m,ll,rr),query_m(idx*2+1,m,r,ll,rr))+add[idx];
}

int query_p(int idx,int l,int r,int k) {
	if (l+1==r) {
		return seg[idx]+add[idx];
	}
	int m=(l+r)>>1;
	if (k<m) return query_p(idx*2,l,m,k)+add[idx];
	else return query_p(idx*2+1,m,r,k)+add[idx];
}

void update(int idx,int l,int r,int ll,int rr,int val) {
	if (ll>=r||rr<=l) return;
	if (ll<=l&&rr>=r) {
		add[idx]+=val;
		return;
	}
	int m=(l+r)>>1;
	update(idx*2,l,m,ll,rr,val);
	update(idx*2+1,m,r,ll,rr,val);
	seg[idx]=max(seg[idx*2]+add[idx*2],seg[idx*2+1]+add[idx*2+1]);
	mn[idx]=min(mn[idx*2]+add[idx*2],mn[idx*2+1]+add[idx*2+1]);
	return;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int minn=-2e9;
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		minn=max(minn,tbl[i]);
		qs[i]=qs[i-1]+tbl[i];
	}
	
	int lastl=-1,lastr=-1;
	int curl=1;
	int cur=0;
	int ans=-2e9;
	for (int i=1;i<=n;i++) {
		cur+=tbl[i];
		if (cur<0) {
			cur=0;
			curl=i+1;
		}
		if (cur>ans) {
			ans=cur;
			lastr=i;
			lastl=curl;
		}
		//ans=max(ans,cur);
	}
	if (ans==0) ans=minn;
	printf("%d\n",ans);
	
	
	
	build(1,1,n+1);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		a++;
		int now=query_p(1,1,n+1,a);
		int il,ir;
		int tmp=query_m(1,1,n+1,1,a,il);
		il++;
		if (tmp>0) {
			tmp=0;
			il=1;
		}
		int left=max(0,now-tbl[a]-tmp);
		int rgt=max(0,query(1,1,n+1,a+1,n+1,ir)-now);
		int nowBest=b+left+rgt;
		
		if (left==0) il=a;
		if (rgt==0) ir=a;



		//printf("%d %d %d %d\n",now,query(1,1,n+1,a+1,n+1),query_m(1,1,n+1,1,a),nowBest);
		//printf("%d %d %d\n",left,rgt,now);

		int dif=b-tbl[a];
		tbl[a]=b;
		
		if (a<lastl||a>lastr) {
			if (nowBest>now) {
				ans=nowBest;
				lastl=il;
				lastr=ir;
			}
			//ans=max(ans,nowBest);
		}
		else {
			ans=nowBest;
			lastl=il;
			lastr=ir;
		}
		update(1,1,n+1,a,n+1,dif);
		printf("%d\n",ans);
	}
	return 0;
}
