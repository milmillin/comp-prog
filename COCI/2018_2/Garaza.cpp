#include <cstdio>
#include <vector>

using namespace std;

int tbl[100100];

struct p {
	int val,cnt;
};

struct node {
	~node() {
		if (l!=NULL) delete l;
		if (r!=NULL) delete r;
	}
	long long cnt;
	vector<p> pre,suf;
	node *l, *r;
	void combine();
	node(node* a) {
		cnt=a->cnt;
		pre=a->pre;
		suf=a->suf;
	}

	node() {

	}
};

int gcd(int a,int b) {
	return (b==0)?a:gcd(b,a%b);
}

void node::combine() {
	if (l==NULL||r==NULL) {
		node* tmp;
		if (l==NULL) tmp=r;
		else tmp=l;
		pre = tmp->pre;
		suf = tmp->suf;
		cnt = tmp->cnt;
		return;
	}
	pre.clear();
	suf.clear();
	pre.insert(pre.begin(),l->pre.begin(),l->pre.end());
	suf.insert(suf.begin(),r->suf.begin(),r->suf.end());
	int gl=l->pre.back().val;
	int gr=r->suf.back().val;
	int xx;
	for (auto i:r->pre) {
		xx=gcd(i.val,gl);
		if (xx==pre.back().val) pre.back().cnt+=i.cnt;
		else pre.push_back(p{xx,i.cnt});
	}
	for (auto i:l->suf) {
		xx=gcd(i.val,gr);
		if (xx==suf.back().val) suf.back().cnt+=i.cnt;
		else suf.push_back(p{xx,i.cnt});
	}

	cnt=l->cnt+r->cnt;
	int cur=0;
	long long c=0;
	for (int i=l->suf.size()-1;i>=0;i--) {
		auto &xx = l->suf[i];
		while (cur<r->pre.size()&&gcd(xx.val,r->pre[cur].val)>1) {
			c+=r->pre[cur].cnt;
			cur++;
		}
		if (cur>0) {
			cnt+=xx.cnt*c;
			//printf("-- %d %d\n",xx.cnt,c);
		}
	}
}

node* build(int l,int r) {
	node *tmp = new node();
	if (l+1==r) {
		tmp->pre.push_back(p{tbl[l],1});
		tmp->suf.push_back(p{tbl[l],1});
		tmp->l=NULL;
		tmp->r=NULL;
		tmp->cnt=(tbl[l]==1)?0:1;
		//printf("%d %d %d\n",l,r,tmp->cnt);
		return tmp;
	}
	int m = (l+r)>>1;
	tmp->l=build(l,m);
	tmp->r=build(m,r);
	tmp->combine();
	//printf("%d %d %d\n",l,r,tmp->cnt);
	return tmp;
}

node* buildQTree(int l,int r) {
	node *tmp = new node();
	if (l+1==r) {
		return tmp;
	}
	int m = (l+r)>>1;
	tmp->l=build(l,m);
	tmp->r=build(m,r);
	return tmp;
}

void update(node* tmp,int l,int r,int k) {
	if (k<l||k>=r) return;
	if (l+1==r) {
		tmp->pre[0].val=tbl[k];
		tmp->suf[0].val=tbl[k];
		tmp->cnt=(tbl[k]==1)?0:1;
		return;
	}
	int m = (l+r)>>1;
	if (k<m) update(tmp->l,l,m,k);
	else update(tmp->r,m,r,k);
	tmp->combine();
}

void query(node* now,node* qq,int l,int r,int ll,int rr) {
	if (rr<=l||ll>=r) {
		qq->cnt=0;
		qq->pre.clear();
		qq->suf.clear();
		qq->pre.push_back(p{1,1});
		qq->suf.push_back(p{1,1});
		return;
	}
	if (ll<=l&&rr>=r) {
		qq->cnt=now->cnt;
		qq->pre.clear();
		qq->suf.clear();
		qq->pre.insert(qq->pre.begin(),now->pre.begin(),now->pre.end());
		qq->suf.insert(qq->suf.begin(),now->suf.begin(),now->suf.end());
		return;
	}
	//node* tmp = new node();
	int m = (l+r) >> 1;
	query(now->l,qq->l,l,m,ll,rr);
	query(now->r,qq->r,m,r,ll,rr);
	qq->combine();
	//printf("--- %d %d %d %d %d\n",l,r,ll,rr,tmp->cnt);
	//return tmp;
}

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	node* root = build(0,n);
	node* rootq = buildQTree(0,n);
	//return 0;
	//for (auto &i:root->pre) {
		//printf("%d %d\n",i.val,i.cnt);
	//}
	//printf("yay\n");
	int a,b,c;
	while (q--) {
		scanf("%d%d%d",&a,&b,&c);
		if (a==1) {
			b--;
			tbl[b]=c;
			update(root,0,n,b);
		} else {
			b--;
			query(root,rootq,0,n,b,c);
			printf("%lld\n",rootq->cnt);
		}	
	}
	//delete root;
	return 0;
}
