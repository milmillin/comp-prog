#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int val;
	node *l,*r;
	node (int _val) {
		val=_val;
		l=r=NULL;
	}
};

node* insert() {
	int x;
	scanf("%d",&x);
	node* tmp = new node(x);
	if (x!=0) return tmp;
	tmp->l=insert();
	tmp->r=insert();	
	if (tmp->l->val>tmp->r->val) swap(tmp->l,tmp->r);
	tmp->val=min(tmp->l->val,tmp->r->val);
	return tmp;
}

vector<int> tbl;

void dfs(node* idx) {
	if (idx->l==NULL) {
		tbl.push_back(idx->val);
		return;
	}
	dfs(idx->l);
	dfs(idx->r);
}

long long inv(int l,int r) {
	if (l+1==r) return 0;
	if (r-l==2) {
		if (tbl[l]>tbl[l+1]) {
			swap(tbl[l],tbl[l+1]);
			return 1;
		}
		return 0;
	}
	int m=(l+r)>>1;
	long long sum=inv(l,m)+inv(m,r);
	int cl=l;
	int cr=m;
	int cur=0;
	int vl,vr;
	vector<int> tmp(r-l);
	while (cur<r-l) {
		vl=(cl==m)?2e9:tbl[cl];
		vr=(cr==r)?2e9:tbl[cr];		
		if (vl<vr) {
			tmp[cur++]=vl;
			sum+=cr-m;
			cl++;
		} else {
			tmp[cur++]=vr;
			cr++;
		}
	}
	for (int i=l;i<r;i++) {
		tbl[i]=tmp[i-l];
	}
	return sum;
}

int main () {
	int n;
	scanf("%d",&n);
	node *root = insert();
	dfs(root);
	printf("%lld\n",inv(0,n));
	//for (auto i:tbl) {
		//printf("%d ",i);
	//}
	//printf("\n");
	return 0;
}
