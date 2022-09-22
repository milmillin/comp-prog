#include <cstdio>
#include <algorithm>

using namespace std;

struct node {
	int val,mx,pre,post;
	node *l,*r;
};

int tbl[200100];

node* build(node *idx,int l,int r) {
	node *now=idx;
	if (now==NULL) {
		now=new node{};
	}
	if (l+1==r) {
		now->val=tbl[l];
		now->mx=now->pre=now->post=max(0,tbl[l]);
		return now;
	}
	int m=(l+r)>>1;
	now->l=build(now->l,l,m);
	now->r=build(now->r,m,r);	
	now->val=now->r->val+now->l->val;
	now->pre=max(now->l->pre,now->l->val+now->r->pre);
	now->post=max(now->r->post,now->r->val+now->l->post);
	now->mx=max(max(now->pre,now->post),max(max(now->l->mx,now->r->mx),now->l->post+now->r->pre));
	return now;
}

struct ei {
	int val,mx,pre,post;
};

ei query(node *idx,int l,int r,int ll,int rr) {
	if (rr<=l||ll>=r) return ei{};
	if (ll<=l&&rr>=r) return ei{idx->val,idx->mx,idx->pre,idx->post};
	int m=(l+r)>>1;
	auto al=query(idx->l,l,m,ll,rr);
	auto ar=query(idx->r,m,r,ll,rr);

	int val=al.val+ar.val;
	int pre=max(al.pre,al.val+ar.pre);
	int post=max(ar.post,ar.val+al.post);
	int mx=max(max(pre,post),max(max(al.mx,ar.mx),al.post+ar.pre));

	return ei{val,mx,pre,post};
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	node* root=new node{};
	root=build(root,0,n);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		printf("%d\n",query(root,0,n,a,b+1).mx);
	}
	return 0;
}
