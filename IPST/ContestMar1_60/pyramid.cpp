#include <cstdio>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

struct node {
	int key,prior;
	int sz;
	node *l,*r;
	node (int _key) {
		key=_key;
		prior=(rand()<<16)^rand();
		sz=1;
		l=r=NULL;
	}
};

void update(node *x) {
	if (!x) return;
	x->sz=((x->l)?x->l->sz:0)+1+((x->r)?x->r->sz:0);
}

void split(node *x,node* &l, node* &r,int key) {
	if (!x) l=r=NULL;
	else if (x->key<key) {
		l=x;
		split(x->r,x->r,r,key);
	} else {
		r=x;
		split(x->l,l,x->l,key);
	}
	update(x);
}

void merge(node* &x, node *l, node *r) {
	if (!l||!r) x=(l)?l:r;
	else if (l->prior>r->prior) {
		x=l;
		merge(l->r,l->r,r);	
	} else {
		x=r;
		merge(r->l,l,r->l);
	}
	update(x);
}

void insert(node* &x,node *n) {
	if (!x) x=n;
	else if (n->prior>x->prior) {
		split(x,n->l,n->r,n->key);
		x=n;
	} else {
		insert((x->key<n->key)?x->r:x->l,n);
	}
	update(x);
}

int query(node *x, int key) {
	if (!x) return 0;
	if (x->key<=key) {
		return ((x->l)?x->l->sz:0)+1+query(x->r,key);
	} else {
		return query(x->l,key);
	}
}

node* bit1[6000];
node* bit2[6000];

void add(node* bit[], int idx, int key) {
	assert(idx!=0);
	while (idx<6000) {
		insert(bit[idx],new node(key));
		idx+=(idx&-idx);
	}
}

int query(node* bit[], int idx, int key) {
	int sum=0;
	while (idx) {
		sum+=query(bit[idx],key);
		idx-=(idx&-idx);
	}
	return sum;
}

int main () {
	srand(time(NULL));
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		int sum=0;
		sum+=query(bit1,5999,a-b);
		sum-=query(bit1,a+10,a-b);
		sum+=query(bit2,a+10,-a-b);
		printf("%d\n",sum);
		add(bit1,a+10,a-b);
		add(bit2,a+10,-a-b);	
	}	
	return 0;
}
