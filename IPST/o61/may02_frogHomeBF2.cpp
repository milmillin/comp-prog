#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int qs[20];
vector<int> pth[100100];

int dep[100100];
int mxdep[100100];
int in[100100];
int ou[100100];
int what[100100];
int ti=1;

void dfs(int x,int p,int d) {
	mxdep[x]=dep[x]=d;
	what[ti]=x;
	in[x]=ti++;
	for (auto i:pth[x]) {
		if (i==p) continue;
		dfs(i,x,d+1);
		mxdep[x]=max(mxdep[x],mxdep[i]);
	}
	ou[x]=ti;
}

struct node {
	int val;
	node *l,*r;
	node(int _val):val(_val),l(0),r(0) {}
};

node* insert(node *x,int l,int r,int k) {
	node *tmp = new node(1);	
	if (x) tmp->val+=x->val;
	if (l+1==r) return tmp;
	int m=(l+r)>>1;
	if (k<m) {
		tmp->l=insert(x?x->l:0,l,m,k);
		tmp->r=x?x->r:0;
	} else {
		tmp->r=insert(x?x->r:0,m,r,k);
		tmp->l=x?x->l:0;
	}
	return tmp;
}

int _query(node *x,int l,int r,int k) {
	if (!x) return 0;
	if (l+1==r) return x->val;
	int m=(l+r)>>1;
	if (k<m) {
		return _query(x->l,l,m,k);
	} else {
		return _query(x->r,m,r,k);
	}
}

int n,k;
node* root[100100];

int query(int x,int d) {
	d+=dep[x];
	if (d>=n) return 0;
	return _query(root[ou[x]-1],0,n,d)-_query(root[in[x]-1],0,n,d);
}

long long dp(int x,int p,int k) {
	long long ans=0;	
	int mx=dep[x];
	for (auto i:pth[x]) {
		if (i==p) continue;
		ans+=dp(i,x,k);
		mx=max(mx,mxdep[i]);
	}
	for (int i=max(k-mxdep[x]+dep[x],1);i<min(mxdep[x]-dep[x]+1,k);i++) {
		int j=k-i;
		//if (j>mxdep[x]-dep[x]) continue;
		long long tmp=0;
		vector<int> aa;
		for (auto ii:pth[x]) {
			if (ii==p) continue;
			//tmp+=query(ii,i-1);
			aa.push_back(query(ii,i-1));
			tmp+=aa.back();
		}
		int cur=0;
		for (auto ii:pth[x]) {
			if (ii==p) continue;
			//int a=query(ii,i-1);
			int b=query(ii,j-1);
			ans+=(tmp-aa[cur++])*b;
		}
	}
	ans+=2*query(x,k);
	//printf("%d %d %lld\n",x,k,ans);
	return ans;
}

void print(node *x) {
	if (!x) return;
	for (int i=0;i<n;i++) {
		printf("%d ",_query(x,0,n,i));
	}
	printf("\n");
}

int main () {
	scanf("%d%d",&n,&k);
	for (int i=0;i<k;i++) {
		scanf("%d",&qs[i]);
	}
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	dfs(1,1,0);
	//for (int i=1;i<=n;i++) {
		//printf("%d %d\n",i,dep[i]);
	//}
	for (int i=1;i<ti;i++) {
		root[i]=insert(root[i-1],0,n,dep[what[i]]);	
		//print(root[i]);
	}
	
	//printf("yay\n");
	for (int i=0;i<k;i++) {
		printf("%lld\n",dp(1,1,qs[i]));
	}
	return 0;
}
