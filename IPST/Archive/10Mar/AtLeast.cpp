#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int mp[100100];
int tbl[100100];

struct qs {
	int id,s,t;
	double val;
	int ans;
};

struct ei {
	int id, val;
};

bool cmp2 (const ei &a, const ei &b) {
	return a.val<b.val;
}

ei tbl2[100100];

int blk_size;

bool cmp (const qs &a, const qs &b) {
	if (a.s/blk_size!=b.s/blk_size) return a.s/blk_size<b.s/blk_size;
	return a.t>b.t;
}

bool cmp1 (const qs &a, const qs &b) {
	return a.id<b.id;
}

vector<qs> q;

long long bit[100100];
int cntt[100100];
long long sum[100100];

void update(int idx,int val,int val2) {
	//printf("update %d %d %d\n",idx,val,val2);
	while (idx<100100) {
		bit[idx]+=val;
		cntt[idx]+=val2;
		idx+=(idx&-idx);
	}
}

long long get(long long *t, int idx) {
	long long sum=0;
	while (idx) {
		sum+=t[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int get(int *t, int idx) {
	int sum=0;
	while (idx) {
		sum+=t[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

void add(int idx) {
	update(mp[idx],tbl[idx],1);
}

void rem(int idx) {
	update(mp[idx],-tbl[idx],-1);
}

double solve (int idx,int s,int t) {
	
	long long sum2=sum[t]-((s)?sum[s-1]:0);
	int cnt2=t-s+1;
	if (idx==0) return (double)sum2/cnt2;

	long long sum1=get(bit,idx);
	int cnt1=get(cntt,idx);
	
	if (cnt2==cnt1) return 0;
	//printf("solve %d %I64d %d %I64d %d\n",idx,sum2,cnt2,sum1,cnt1);
	return (double)(sum2-sum1)/(cnt2-cnt1);
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	blk_size=floor(sqrt(n));
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		tbl2[i]=ei{i,tbl[i]};
		sum[i]=((i)?sum[i-1]:0)+tbl[i];
	}
	sort(tbl2,tbl2+n,cmp2);
	int cur=1;
	for (int i=0;i<n;i++) {
		mp[tbl2[i].id]=cur;
		cur++;
	}

	int a,b;
	double c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%lf",&a,&b,&c);
		q.push_back(qs{i,a-1,b-1,c,0});
	}
	sort(q.begin(),q.end(),cmp);
	int left=0;
	int rgt=-1;
	for (int i=0;i<m;i++) {
		
		while (left>q[i].s) {
			left--;
			add(left);
		}
		while (left<q[i].s) {
			rem(left);
			left++;
		}
		while (rgt<q[i].t) {
			rgt++;
			add(rgt);
			//printf("%d\n",rgt);
		}
		//printf("yay");
		while (rgt>q[i].t) {
			rem(rgt);
			rgt--;
		}
		/*
		for (int j=1;j<cur;j++) {
			printf("%d ",get(cntt,j));
		}
	*/	
		//printf("\n");
		int f=0;
		int l=cur;
		while (f<l) {
			int m=(f+l)>>1;
			//printf("%d %f\n",m,solve(m,q[i].s,q[i].t));
			if (solve(m,q[i].s,q[i].t)>=q[i].val) l=m;
			else f=m+1;
		}
		if (l==cur) q[i].ans=-1;
		else q[i].ans=get(cntt,l);
	}
	sort(q.begin(),q.end(),cmp1);
	for (int i=0;i<m;i++) {
		printf("%d\n",q[i].ans);
	}
	return 0;
}
