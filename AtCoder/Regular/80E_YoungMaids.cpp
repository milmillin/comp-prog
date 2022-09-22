#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int tbl[2][100100];

struct node {
	int val;
	int idx;
	node *left,*rgt;
};

struct ei {
	pair<int,int> val;
	pair<int,int> idx;
	int ll, rr;
};

bool operator<(const ei &a, const ei &b) {
	return a.val>b.val;
}

priority_queue<ei> qq;

node* build(int l,int r,int tree) {
	node* tmp = new node();
	if (l+1==r) {
		tmp->val=tbl[tree][l];
		tmp->idx=l*2+tree;
		tmp->rgt=0;
		tmp->left=0;
		return tmp;
	}
	int m=(l+r)>>1;
	node* ll = build(l,m,tree);
	node* rr = build(m,r,tree);
	if (ll->val<rr->val) {
		tmp->val=ll->val;
		tmp->idx=ll->idx;
	} else {
		tmp->val=rr->val;
		tmp->idx=rr->idx;
	}
	tmp->left=ll;
	tmp->rgt=rr;
	//printf("%d %d %d %d %d\n",tree,l,r,tmp->val,tmp->idx);
	return tmp;
}

node* root[4];

int getElem(int idx) {
	return tbl[idx%2][idx/2];
}

pair<int,int> trQuery(node *idx,int ll,int rr,int ql,int qr) {
	if (ql<=ll&&qr>=rr) return {idx->val,idx->idx};
	if (qr<=ll) return {2e9,2e9};
	if (ql>=rr) return {2e9,2e9};
	int mm=(ll+rr)>>1;
	if (ql>=mm) return trQuery(idx->rgt,mm,rr,ql,qr);
	if (qr<=mm) return trQuery(idx->left,ll,mm,ql,qr);
	auto l = trQuery(idx->left,ll,mm,ql,qr);
	auto r = trQuery(idx->rgt,mm,rr,ql,qr);
	if (l.first<r.first) return l;
	return r;
}

int n;


ei query(int ll,int rr) {
	//printf("call %d %d\n",ll,rr);
	if (rr-ll==2) {
		return {{getElem(ll),getElem(ll+1)},{ll,ll+1},ll,rr};
	}
	int tr=ll%2;
	auto left = trQuery(root[tr],0,n/2,ll/2,rr/2);
	int leftId = left.second+1;
	auto rgtt = trQuery(root[!tr],0,n/2,leftId/2,(rr+1)/2);
	
	return {{left.first,rgtt.first},{left.second,rgtt.second},ll,rr};
	//query(ll,left.second,dep);
	//query(left.second+1,rgtt.second,dep+1);
	//query(rgtt.second+1,rr,dep);


	//anss.push_back({dep,{left.first,rgtt.first}});
}

int main () {
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i%2][i/2]);
	}
	//for (int i=0;i<n;i++) {
		//printf("%d,%d ",tbl[0][i],tbl[1][i]);
	//}
	//printf("\n");
	root[0]=build(0,n/2,0);
	root[1]=build(0,n/2,1);
	
	auto fst = query(0,n);
	qq.push(fst);
	while (!qq.empty()) {
		auto cur = qq.top();
		qq.pop();
		ei tmp;
		printf("%d %d ",cur.val.first,cur.val.second);
		if (cur.ll!=cur.idx.first) {
			tmp=query(cur.ll,cur.idx.first);
			qq.push(tmp);
		}
		if (cur.idx.first+1!=cur.idx.second) {
			tmp = query(cur.idx.first+1,cur.idx.second);
			qq.push(tmp);
		}
		if (cur.idx.second+1!=cur.rr) {
			tmp = query(cur.idx.second+1,cur.rr);
			qq.push(tmp);
		}
			//query(ll,left.second,dep);
			//query(left.second+1,rgtt.second,dep+1);
			//query(rgtt.second+1,rr,dep);
	}
	printf("\n");
	return 0;
}
