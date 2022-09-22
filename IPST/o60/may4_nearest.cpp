#include <cstdio>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct node {
	int key;
	int prior;
	int ll,rr;
	int ans;
	node *l,*r;
	node(int _key) {
		key=_key;
		prior=(rand()<<16)^rand();
		ll=rr=key;
		ans=1e9;
		l=r=NULL;
	}
};

void update(node *x) {
	if (!x) return;
	x->ll=(x->l)?x->l->ll:x->key;
	x->rr=(x->r)?x->r->rr:x->key;
	x->ans=1e9;
	if (x->l) x->ans=min(x->ans,min(x->l->ans,x->key-x->l->rr));
	if (x->r) x->ans=min(x->ans,min(x->r->ans,x->r->ll-x->key));	
}

void split(node* x,node* &l, node* &r,int key) {
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

void merge(node* &x,node *l, node *r) {
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

void insert(node* &x, node *n) {
	if (!x) x=n;
	else if (n->prior>x->prior) {
		split(x,n->l,n->r,n->key);
		x=n;
	} else {
		insert((x->key<n->key)?x->r:x->l,n);
	}
	update(x);
}

void erase(node* &x, int key) {
	if (!x) return;
	if (x->key==key) {
		//node *tmp;
		merge(x,x->l,x->r);
		//x=tmp;
	} else {
		erase((x->key<key)?x->r:x->l,key);
	}
	update(x);
}

map<int,node*> root;

int cur[100100];

int main () {
	srand(time(NULL));
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<n;i++) {
		insert(root[0],new node(i));
	}
	long long ans=0;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		erase(root[cur[a]],a);
		insert(root[b],new node(a));	
		cur[a]=b;
		//printf("%d\n",root[b]->ans);
		int tmp=root[b]->ans;
		if (tmp!=1e9) ans+=tmp;
	}
	printf("%lld\n",ans);
	return 0;
}
