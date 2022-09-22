#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int l[40100];
int r[40100];

struct node {
	int val;
	node *l,*r;
};

node* insert(node* idx,int l,int r,int ll,int rr,int val) {
	if (rr<=l||ll>=r) return idx;
	node* now=idx;
	if (now==NULL) now=new node{0,NULL,NULL};
	if (ll<=l&&rr>=r) {
		now->val=max(now->val,val);
		return now;
	}
	int m=(l+r)>>1;
	now->l=insert(now->l,l,m,ll,rr,val);
	now->r=insert(now->r,m,r,ll,rr,val);
	return now;
}

int query(node* idx,int l,int r,int k) {
	if (idx==NULL) return 0;
	if (k<l||k>=r) return 0;
	if (l+1==r) return idx->val;
	int m=(l+r)>>1;
	return max(idx->val,max(query(idx->l,l,m,k),query(idx->r,m,r,k)));
}

void f() {
	int n;
	scanf("%d",&n);
	//int a,b;
	map<int,int> mp;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&l[i],&r[i]);
		mp[l[i]];
		mp[r[i]];
	}
	int cnt=0;
	for (auto& it:mp) {
		it.second=cnt++;
	}
	node* root=NULL;
	for (int i=0;i<n;i++) {
		l[i]=mp[l[i]];
		r[i]=mp[r[i]];
		//printf("%d %d %d\n",i,);
		root=insert(root,0,cnt,l[i],r[i]+1,i+1);
	}
	//printf("yay\n");
	set<int> st;
	for (int i=0;i<cnt;i++) {
		int tmp=query(root,0,cnt,i);
		//printf("%d\n",tmp);
		st.insert(tmp);	
	}
	printf("%d\n",st.size());
}

int main() {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
