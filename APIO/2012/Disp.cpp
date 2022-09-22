#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct node {
	int key;
	int prior;
	long long sum;
	int cnt;
	node *l,*r;
	node (int _val) {
		key=_val;
		sum=_val;
		cnt=1;
		prior=(rand()<<16)^rand();
		l=r=NULL;
	}
};

void update(node *x) {
	if (!x) return;
	x->sum=x->key+((x->l)?x->l->sum:0)+((x->r)?x->r->sum:0);
	x->cnt=1+((x->l)?x->l->cnt:0)+((x->r)?x->r->cnt:0);
}

void split(node *x,node* &l, node* &r,int key) {
	if (!x) l=r=NULL;
	else if (x->key<key) {
		l=x;
		split (x->r,x->r,r,key);
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
		merge(x->r,x->r,r);
	} else {
		x=r;
		merge(x->l,l,x->l);
	}
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

int query(node *x, long long sum) {
	if (!x) return 0;
	long long tmp=((x->l)?x->l->sum:0)+x->key;
	if (sum>=tmp) return ((x->l)?x->l->cnt:0)+1+query(x->r,sum-tmp);
	return query(x->l,sum);
}

void combine(node* &a, node *b) {
	if (!b) return;
	combine(a,b->l);
	combine(a,b->r);
	b->l=NULL;
	b->r=NULL;
	b->cnt=1;
	b->sum=b->key;
	insert(a,b);	
}

void print(node *x) {
	if (!x) return;
	print(x->l);
	printf("%d ",x->key);
	print(x->r);
}

int c[100100];
int l[100100];
//vector<int> pth[100100];
int p[100100];
node* nd[100100];

int main () {
	//printf("yay\n");
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d",&p[i],&c[i],&l[i]);
		//if (x) pth[x].push_back(i);
		insert(nd[i],new node(c[i]));
	}
	long long ans=0;
	for (int i=n;i>=1;i--) {
		//print(nd[i]);
		//printf("\n");
		ans=max(ans,(long long)query(nd[i],m)*l[i]);	
		//printf("%d %d %d\n",i,l[i],query(nd[i],m));
		if (i==1) break;
		if (nd[i]->cnt>nd[p[i]]->cnt) swap(nd[i],nd[p[i]]);
		combine(nd[p[i]],nd[i]);	
	}	
	printf("%lld\n",ans);
	return 0;
}
