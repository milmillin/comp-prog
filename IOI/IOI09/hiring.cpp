#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct p {
	int s;
	int q;
	int id;
};

bool operator< (const p &a, const p &b) {
	if (a.s*b.q!=b.s*a.q) return a.s*b.q<b.s*a.q; 
	return a.q>b.q;
}

p tbl[500100];

struct ans{
	int num;
	long long a,b;
	int s;
};

bool operator<(const ans &a, const ans &b) {
	if (a.num!=b.num) return a.num<b.num;
	return a.a*b.b>a.b*b.a;
}

struct node {
	int key;
	int prior;
	int val;
	int id;
	int cnt;
	long long sum;

	node *l,*r;

	node(int _key,int _val,int _id): key(_key),prior((rand()<<16)^rand()),val(_val),id(_id),cnt(1),sum(_val),l(0),r(0) {}
};

void update(node *x) {
	if (!x) return;
	x->cnt=1;
	x->sum=x->val;
	if (x->l) {
		x->cnt+=x->l->cnt;
		x->sum+=x->l->sum;
	}
	if (x->r) {
		x->cnt+=x->r->cnt;
		x->sum+=x->r->sum;
	}
}

void split(node *x,node* &l, node* &r,int key) {
	if (!x) l=r=0;
	else if (x->key<key) {
		l=x;
		split(x->r,x->r,r,key);
	} else{
		r=x;
		split(x->l,l,x->l,key);
	}
	update(x);
}

void insert(node* &x,node *p) {
	if (!x) x=p;
	else if (p->prior>x->prior) {
		split(x,p->l,p->r,p->key);
		x=p;
	} else {
		insert(x->key<p->key?x->r:x->l,p);
	}
	update(x);
}

void print(node* x) {
	if (!x) return;
	print(x->l);
	printf("%d\n",x->id);
	print(x->r);
}

struct pp {
	long long a,b;

	pp operator+(const pp &r) const {
		return pp{a+r.a,b+r.b};
	}
};

pp query(node *x,long long pre,long long l,long long r,bool pr) {
	if (!x) return pp{0,0};
	long long qq=x->val;
	int cnt=1;
	if (x->l) qq+=x->l->sum,cnt+=x->l->cnt;
	if (l*(qq+pre)<=r) {
		if (pr) {
			print(x->l);
			printf("%d\n",x->id);
		}
		return pp{cnt,qq}+query(x->r,qq+pre,l,r,pr);
	} else {
		return query(x->l,pre,l,r,pr);
	}
}

int main () {
	int n;
	long long w;
	scanf("%d%lld",&n,&w);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&tbl[i].s,&tbl[i].q);
		tbl[i].id=i;
	}
	sort(tbl+1,tbl+n+1);

	ans a={0,0,0,0};
	
	node* root=NULL;

	for (int i=1;i<=n;i++) {
		insert(root,new node(tbl[i].q,tbl[i].q,tbl[i].id));	
		pp res=query(root,0,tbl[i].s,w*tbl[i].q,false);
		a=max(a,ans{(int)res.a,tbl[i].s*(res.b),tbl[i].q,i});
	}
	printf("%d\n",a.num);
	root=0;
	for (int i=1;i<=a.s;i++) {
		insert(root,new node(tbl[i].q,tbl[i].q,tbl[i].id));	
	}
	query(root,0,tbl[a.s].s,w*tbl[a.s].q,true);
	return 0;
}
