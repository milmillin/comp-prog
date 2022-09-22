#include <cstdio>
#include <algorithm>

using namespace std;

struct node {
	int val;
	int mx;
	int mxcnt;
	int lazed;
	node *l,*r;
};


node* root;

node* build (node *idx,int l,int r) {
	node *now=idx;
	if (now==NULL) {
		now=new node{};
	}
	if (l+1==r) {
		now->val=now->mx=now->lazed=0;
		now->mxcnt=1;
		return now;
	}
	int m=(l+r)>>1;
	now->val=now->mx=now->lazed=0;
	now->mxcnt=1;
	now->l=build(now->l,l,m);
	now->r=build(now->r,m,r);
	return now;
}

int query(node *idx,int l,int r,int k) {
	//printf("q %d %d %d\n",l,r,k);
	if (k>=r||k<l) return -2e9;
	if (l+1==r) {
		return idx->mx;
	}
	if (idx->lazed) {
		idx->l->mx+=idx->lazed;
		idx->r->mx+=idx->lazed;
		idx->l->lazed+=idx->lazed;
		idx->r->lazed+=idx->lazed;
		idx->lazed=0;
	}
	int m=(l+r)>>1;
	if (k<m) return query(idx->l,l,m,k);
	else return query(idx->r,m,r,k);
}

void update(node* idx,int l,int r,int ll,int rr,int k) {
	if (rr<=l||ll>=r) return;
	if (ll<=l&&rr>=r) {
		idx->mx+=k;
		idx->lazed+=k;
		return;
	}	
	if (idx->lazed) {
		idx->l->mx+=idx->lazed;
		idx->r->mx+=idx->lazed;
		idx->l->lazed+=idx->lazed;
		idx->r->lazed+=idx->lazed;
		idx->lazed=0;
	}	
	int m=(l+r)>>1;
	update(idx->l,l,m,ll,rr,k);
	update(idx->r,m,r,ll,rr,k);
	idx->mx=max(idx->l->mx,idx->r->mx);
	idx->mxcnt=0;
	//printf("-- %d %d %d %d\n",idx->l->mx,idx->l->mxcnt,idx->r->mx,idx->r->mxcnt);
	if (idx->l->mx==idx->mx) idx->mxcnt+=idx->l->mxcnt;
	if (idx->r->mx==idx->mx) idx->mxcnt+=idx->r->mxcnt;
	if (idx->l->mx==idx->r->mx) {
		int a=query(idx->l,l,m,m-1);
		int b=query(idx->r,m,r,m);
		if (a==b&&a==idx->mx) idx->mxcnt--;
	}
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);

	root=build(root,0,n);

	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		update(root,0,n,a-1,b,c);	
		//for (int j=0;j<n;j++) {
			//printf("%d ",query(root,0,n,j));
		//}
		//printf("\n");
		printf("%d %d\n",root->mx,root->mxcnt);
	}
	return 0;
}
