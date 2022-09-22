#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct bar {
	int idx,hgt;
};

bool cmp (const bar &a, const bar &b) {
	return a.hgt>b.hgt;
}

struct node {
	bool mrk;
	int pre,suf,w;
	node *left,*right;
	node* insert(int l,int r,int k);
};

struct param {
	int w,pre,suf;
};

node* null=new node{0,0,0,0,NULL,NULL};

node* node::insert(int l,int r,int k) {
	if (l<=k&&k<r) {
		if (l+1==r) {
			return new node {true,1,1,1,null,null};
		}
		int m=(l+r)>>1;
		node* ll=this->left->insert(l,m,k);
		node* rr=this->right->insert(m,r,k);
		int p=ll->pre;
		if (p==m-l) p+=rr->pre;
		int s=rr->suf;
		if (s==r-m) s+=ll->suf;
		return new node {true,p,s,max(ll->w,max(rr->w,ll->suf+rr->pre)),ll,rr};
	}
	return this;
}

param query(node* nd,int l,int r,int from,int to) {
	//printf("%d %d %d %d\n",l,r,from,to);
	if (from>=r||to<l) return param{0,0,0};
	if (from<=l&&to>=r-1) return param{nd->w,nd->pre,nd->suf};
	int m=(l+r)>>1;
	param ll=query(nd->left,l,m,from,to);
	param rr=query(nd->right,m,r,from,to);
	if (to<m) return ll;
	if (from>=m) return rr;
	//printf("%d %d\n",ll,rr);
	int p = ll.pre;
	if (m-l==p) p+=rr.pre;
	int s = rr.suf;
	if (r-m==s) s+=ll.suf;
	return param{max(ll.w,max(rr.w,ll.suf+rr.pre)),p,s};
}

//void pp(node* nd,int l,int r) {
	//printf("%d %d %d %d %d\n",nd->w,nd->pre,nd->suf,l,r);
	//if (l+1==r) return;
	//int m=(l+r)>>1;
	//pp(nd->left,l,m);
	//pp(nd->right,m,r);
//}

node* root[300100];

int main () {
	int n;
	scanf("%d",&n);
	int x;
	vector<bar> tbl;
	tbl.reserve(n+1);
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		tbl.push_back(bar{i,x});
	}
	sort(tbl.begin(),tbl.end(),cmp);
	null->left=null->right=null;
	for (int i=0;i<n;i++) {
		root[i]=((i)?root[i-1]:null)->insert(0,n,tbl[i].idx);
	}

	//for (int i=0;i<n;i++) {
		//pp(root[i],0,n);
		//printf("---\n");
	//}

	int q;
	scanf("%d",&q);
	int a,b,c;
	while (q--) {
		scanf("%d%d%d",&a,&b,&c);
		a--;
		b--;
		int lo=0;
		int hi=n;
		int mid;
		int ans=-1;
		while (lo<hi) {
			mid=(lo+hi)>>1;
			//printf("%d\n",mid);
			int tmp=query(root[mid],0,n,a,b).w;
			//printf("-%d\n",tmp);
			if (tmp<c) {
				lo=mid+1;
				//printf("no\n");
			} else {
				hi=mid;
				//printf("yes\n");
				ans=max(ans,tbl[hi].hgt);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
