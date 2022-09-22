#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

#ifdef debug
#include "grader.cpp"
#endif

using namespace std;

int* tbl;

struct event {
	int x,val;
};

bool operator< (const event &a, const event &b) {
	if (a.x!=b.x) return a.x<b.x;
	return a.val<b.val;
}

int seg[300100];

void build(int idx,int l,int r) {
	if (l+1==r) {
		seg[idx]=tbl[l];
		return;
	}
	int m=(l+r)>>1;
	build(idx*2+1,l,m);
	build(idx*2+2,m,r);
	seg[idx]=max(seg[idx*2+1],seg[idx*2+2]);
}

int query(int idx,int l,int r,int ll,int rr) {
	if (ll>=r||rr<=l) return -2e9;
	if (ll<=l&&rr>=r) return seg[idx];
	int m=(l+r)>>1;
	return max(query(idx*2+1,l,m,ll,rr),query(idx*2+2,m,r,ll,rr));	
}

struct node {
	int key,prior;
	int cnt;
	node *l,*r;
	node (int _key) {
		key=_key;
		cnt=1;
		prior=(rand()<<16)^rand();
		l=r=NULL;
	}
};

void update(node *x) {
	if (!x) return;
	x->cnt=((x->l)?x->l->cnt:0)+1+((x->r)?x->r->cnt:0);
}

void split(node *x, node* &l, node* &r,int key) {
	if (!x) l=r=NULL;
	else if (x->key<=key) {
		l=x;
		split(x->r,x->r,r,key);	
	} else {
		r=x;
		split(x->l,l,x->l,key);
	}
	update(x);
}

void merge(node* &x, node* l, node* r) {
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
		insert((x->key>n->key)?x->l:x->r,n);
	}
	update(x);
}

int getkth(node *x,int k) {
	if (!x) return -1;
	int tmp = ((x->l)?x->l->cnt:0)+1;
	//printf("-- %d %d\n",tmp,k);
	if (tmp==k) return x->key;
	if (tmp<k) return getkth(x->r,k-tmp);
	return getkth(x->l,k);
}

void rem(node* &x,int key1,int key2) {
	node *a, *b, *c,*d;
	split(x,a,b,key1-1);
	split(b,c,d,key2-1);
	merge(x,a,d);	
}

void ptree(node *x) {
	if (!x) return;
	ptree(x->l);
	printf("%d ",x->key);
	ptree(x->r);
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
	//printf("yay\n");
	tbl=K;		
	build(0,0,N-1);
	node* root=NULL;
	for (int i=0;i<N;i++) {
		insert(root,new node(i));
	}
	vector<event> events;
	for (int i=0;i<C;i++) {
		int c=getkth(root,S[i]);
		int a=getkth(root,S[i]+1);
		int b=getkth(root,E[i]+1);	
		rem(root,a,b);
		//ei.push_back(comp{a,b});	
		//printf("%d %d\n",c+1,b);
		if (query(0,0,N-1,c+1,b)<R) {
			events.push_back(event{c+1,1});
			events.push_back(event{b,-1});
		}
	}
	sort(events.begin(),events.end());
	int cnt=0;
	int mx=-1;
	int idx=0;
	for (auto &e:events) {
		cnt+=e.val;
		if (cnt>mx) {
			mx=cnt;
			idx=e.x;
		}
	}
	return idx;
}
