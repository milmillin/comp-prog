#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct node {
	int key;
	int prior;
	int prob;
	node *l,*r;	

	node (int _key): key(_key),prior((rand()<<16)^rand()),prob(0),l(0),r(0) {}
};

void prob(node *x) {
	if (!x) return;
	if (!x->prob) return;
	x->key+=x->prob;
	if (x->l) x->l->prob+=x->prob;
	if (x->r) x->r->prob+=x->prob;
	x->prob=0;
}

void split (node *x,node* &l, node* &r, int key) {
	prob(x);
	if (!x) l=r=NULL;
	else if (x->key<key) {
		l=x;
		split(x->r,x->r,r,key);
	} else {
		r=x;
		split(x->l,l,x->l,key);
	}
}

void merge(node* &x,node *l,node *r) {
	prob(l);
	prob(r);
	if (!l||!r) x=(l)?l:r;
	else if (l->prior>r->prior) {
		x=l;
		merge(x->r,x->r,r);
	} else {
		x=r;
		merge(x->l,l,x->l);
	}
}

void insert(node* &x, node *n) {
	prob(x);
	if (!x) x=n;
	else if (n->prior>x->prior) {
		split(x,n->l,n->r,n->key);
		x=n;
	} else {
		insert((x->key<n->key)?x->r:x->l,n);
	}
}

bool find(node *x,int key) {
	prob(x);
	if (!x) return false;
	if (x->key==key) return true;
	return find((x->key<key)?x->r:x->l,key);
}

void query(node* &x,int a,int b,int c) {
	//prob(x);
	if (!find(x,a)) return;
	node *p1,*p2;
	split(x,p1,p2,a);
	if (p1) p1->prob+=b;
	if (p2) p2->prob+=c;
	merge(x,p2,p1);
}

void print(node *x) {
	if (!x) return;
	print(x->l);
	printf("%d ",x->key);
	print(x->r);
}

int main () {
	node *root=0;
	int n,q;
	scanf("%d%d",&n,&q);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		insert(root,new node(x));
	}
	//print(root);
	//printf("\n");
	int a,b,c;
	for (int i=0;i<q;i++) {
		scanf("%d",&x);
		if (x==1) {
			scanf("%d",&a);
			printf("%d\n",find(root,a));
		} else {
			scanf("%d%d%d",&a,&b,&c);
			query(root,a,b,c);
		}
		//print(root);
		//printf("\n");
	}
	return 0;
}
