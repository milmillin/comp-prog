#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct node {
	int key;
	int prior;
	bool swp;
	int cnt;
	node *l,*r;

	node(int k): key(k),prior((rand()<<16)^rand()),swp(false),cnt(1),
	l(0),r(0) {}
};

void prob(node *x) {
	if (!x) return;
	if (!x->swp) return;
	x->swp=false;
	swap(x->l,x->r);
	if (x->l) x->l->swp^=1;
	if (x->r) x->r->swp^=1;
}

void update(node *x) {
	if (!x) return;
	prob(x);
	x->cnt=1+((x->l)?x->l->cnt:0)+((x->r)?x->r->cnt:0);	
}

void split (node *x,node* &l,node* &r,int key) {
	prob(x);
	if (!x) l=r=NULL;
	else {
		int cntl=1+((x->l)?x->l->cnt:0);
		if (cntl<=key) {
			l=x;
			split(x->r,x->r,r,key-cntl);
		} else {
			r=x;
			split(x->l,l,x->l,key);
		}
	}
	update(x);
}

void merge (node* &x, node *l,node *r) {
	prob(l);
	prob(r);
	if (!l||!r) x=(l)?l:r;
	else if (l->prior>r->prior) {
		x=l;
		merge(x->r,x->r,r);
	}else {
		x=r;
		merge(x->l,l,x->l);
	}
	update(x);
}

void insert (node* &x, node *n) {
	merge(x,x,n);
}

void swp(node* &x,int l) {
	prob(x);
	node *p1,*p2;
	split(x,p1,p2,l);	
	p1->swp^=1;
	merge(x,p1,p2);
}

node* getAt(node* x,int id) {
	if (!x) return NULL;
	prob(x);
	int cntl=1+((x->l)?x->l->cnt:0);
	if (cntl==id) return x;
	else if (cntl>id) return getAt(x->l,id);
	else return getAt(x->r,id-cntl);
}

int main () {
	int n;
	scanf("%d",&n);
	node *root=NULL;
	int x;	
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		insert(root,new node(x));
	}
	int cur;
	int cnt=0;
	while ((cur=getAt(root,1)->key)!=1) {
		swp(root,cur);
		cnt++;	
	}
	printf("%d\n",cnt);
	return 0;
}
