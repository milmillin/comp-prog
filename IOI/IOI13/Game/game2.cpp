#include "game.h"

#ifdef debug
#include "grader.cpp"
#endif

#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <queue>
//#include <iostream>

using namespace std;

long long gcd2(long long X, long long Y) {
	long long tmp;
	while (X != Y && Y != 0) {
		tmp = X;
		X = Y;
		Y = tmp % Y;
	}
    return X;
}


struct node {
	pair<int,int> key;	//col,row
	int prior;
	long long val;
	long long gcd;
	node *l, *r;

	node(pair<int,int> _key,long long _val): key(_key),prior((rand()<<16)^rand()),val(_val),gcd(_val),/*mn(_key),mx(_key),*/l(0),r(0) {}

	~node() {
		if (l) delete l;
		if (r) delete r;
	}

	//static void print(node *x) {
		//if (!x) return;
		//print(x->l);
		////printf("%d,%lld ",x->key,x->val);
		//print(x->r);
	//}

	static void update(node *x) {
		if (!x) return;
		x->gcd=x->val;
		if (x->l) {
			x->gcd=gcd2(x->gcd,x->l->gcd);
		}
		if (x->r) {
			x->gcd=gcd2(x->gcd,x->r->gcd);
		}
	}	

	static bool change(node *x,const pair<int,int> &key,long long newval) {
		if (!x) return false;
		if (x->key==key) {
			x->val=newval;
			update(x);
			return true;
		}
		bool res=change((x->key<key)?x->r:x->l,key,newval);
		update(x);
		return res;
	}

	static void split(node *x,node* &l, node* &r,pair<int,int> key) {
		//stepcnt++;
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

	static void merge(node* &x,node *l,node *r) {
		//stepcnt++;
		if(!l||!r) x=(l)?l:r;
		else if (l->prior>r->prior) {
			x=l;
			merge(x->r,x->r,r);
		} else {
			x=r;
			merge(x->l,l,x->l);
		}
		update(x);
	}

	static void insert(node* &x, node *n) {
		if (!x) x=n;
		else if (n->prior>x->prior) {
			split(x,n->l,n->r,n->key);
			x=n;
		} else {
			insert((x->key<n->key)?x->r:x->l,n);
		}
		update(x);
	}

	static long long query(node* &x, int lo,int hi) {
		//printf("query %d %d\n",lo,hi);
		node *l,*m,*r;
		split(x,l,m,{lo,-1});
		split(m,m,r,{hi,1e9+7});
		//print(m);
		//printf("\n");
		long long ans=(m)?m->gcd:0;
		merge(m,m,r);
		merge(x,l,m);
		return ans;
	}
};

int maxR,maxC;
struct segnode {
	node *treap;										
	segnode *l,*r;

	segnode(): treap(0),l(0),r(0) {}

	static segnode* insert(segnode *x, int lo,int hi,int posR,int posC,long long val) {
		segnode *cur;
		if (x) cur=x;
		else cur=new segnode();
		bool res=node::change(cur->treap,{posC,posR},val);
		if (!res) node::insert(cur->treap,new node({posC,posR},val));	
		if (lo+1==hi) return cur;
		int m=(lo+hi)>>1;	
		if (posR<m) {
			cur->l=insert(cur->l,lo,m,posR,posC,val);
		} else {
			cur->r=insert(cur->r,m,hi,posR,posC,val);
		}
		return cur;			
	}	
	
	static long long query(segnode *x, int lo, int hi,int sR,int sC,int eR,int eC) {
		//printf("segquery %d %d\n",lo,hi);
		if (!x) return 0;
		if (sR>=hi||eR<lo) return 0;
		if (sR<=lo&&eR>=hi-1) return node::query(x->treap,sC,eC);
		int m=(lo+hi)>>1;
		return gcd2(query(x->l,lo,m,sR,sC,eR,eC),query(x->r,m,hi,sR,sC,eR,eC));
	}
};

segnode* root;

void init(int R, int C) {
	maxR=R;
	maxC=C;
}

void update(int P, int Q, long long K) {
	root=segnode::insert(root,0,maxR,P,Q,K);	
}


long long calculate(int P, int Q, int U, int V) {
	return segnode::query(root,0,maxR,P,Q,U,V);
}
