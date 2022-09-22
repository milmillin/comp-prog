#include <cstdio>
#include <algorithm>

using namespace std;

struct node {
	int val;
	node *l,*r;
};

node* insert(node* idx,int l,int r,int k,int val) {
	node* cur=idx;
	if (idx==NULL) cur=new node{(int)2e9,NULL,NULL};
	if (k<l||k>=r) return cur;
	if (l+1==r) {
		cur->val=val;
		return cur;
	}
	int m=(l+r)>>1;
	cur->l=insert(cur->l,l,m,k,val);
	cur->r=insert(cur->r,m,r,k,val);				
	cur->val=min(cur->l->val,cur->r->val);
	return cur;
}

void update(node* idx,int l,int r,int k,int val) {
	if (k<l||k>=r) return;
	if (l+1==r) {
		idx->val=min(idx->val,val);
		return;
	}
	int m=(l+r)>>1;
	update(idx->l,l,m,k,val);
	update(idx->r,m,r,k,val);
	idx->val=min(idx->l->val,idx->r->val);
	return;
}

int query(node *idx,int l,int r,int ll,int rr) {
	if (rr<=l||ll>=r) return 2e9;
	if (ll<=l&&rr>=r) return idx->val;
	int m=(l+r)>>1;
	return min(query(idx->l,l,m,ll,rr),query(idx->r,m,r,ll,rr));
}

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	
	return 0;
}
