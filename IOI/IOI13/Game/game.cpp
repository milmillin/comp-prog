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

pair<int,int> inv(const pair<int,int> &x) {
	return {x.second,x.first};
}


int stepcnt;

struct node {
	pair<int,int> key;	//col,row
	int prior;
	long long val;
	long long gcd;
	//pair<int,int> mn;
	//pair<int,int> mx;
	node *l, *r;

	node(pair<int,int> _key,long long _val): key(_key),prior((rand()<<16)^rand()),val(_val),gcd(_val),/*mn(_key),mx(_key),*/l(0),r(0) {}

	~node() {
		if (l) delete l;
		if (r) delete r;
	}

	static void print(node *x) {
		if (!x) return;
		print(x->l);
		printf("%d,%d:%lld,%lld ",x->key.second,x->key.first,x->val,x->gcd);
		print(x->r);
	}

	static void update(node *x) {
		if (!x) return;
		x->gcd=x->val;
		//x->mn=x->mx=x->key;
		if (x->l) {
			x->gcd=gcd2(x->gcd,x->l->gcd);
			//x->mn=min(x->mn,x->l->mn);	
		}
		if (x->r) {
			x->gcd=gcd2(x->gcd,x->r->gcd);
			//x->mx=max(x->mx,x->r->mx);
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

	static bool erase(node* &x, pair<int,int> key) {
		if (!x) return false;
		if (x->key==key) {
			node *tmp=x;
			merge(x,x->l,x->r);
			tmp->l=tmp->r=NULL;
			//delete tmp;
			update(x);
			return true;
		} else {
			bool res=erase(x->key<key?x->r:x->l,key);
			update(x);
			return res;
		}
	}

	static void insertFrom(node* &dest,node* src) {
		if (!src) return;
		insert(dest,new node(src->key,src->val));
		insertFrom(dest,src->l);
		insertFrom(dest,src->r);
	}

	static void eraseFrom(node* &dest,node* src) {
		if (!src) return;
		assert(erase(dest,src->key));
		//erase(dest,src->key);
		eraseFrom(dest,src->l);
		eraseFrom(dest,src->r);
	}

	static long long query(node* &x, int lo,int hi) {
		node *l,*m,*r;
		split(x,l,m,{lo,-1});
		split(m,m,r,{hi,1e9+7});
		long long ans=(m)?m->gcd:0;
		merge(m,m,r);
		merge(x,l,m);
		return ans;
	}

};

struct listnode {
	int key;
	node *val;
	listnode *prv,*nxt;

	listnode(int _key): key(_key),val(0),prv(0),nxt(0) {}

	static void insert(listnode *x,listnode *n) {
		if (x->prv) {
			x->prv->nxt=n;
		}
		n->prv=x->prv;
		n->nxt=x;
		x->prv=n;
	}	
};

listnode* last=new listnode(1e9+7);

struct cluster {
	node *big;
	listnode *fst,*lst;
	int size;
	
	cluster(listnode *init): big(0),fst(init),lst(init),size(1) {}

	listnode* find(int val) {
		//printf("%d %d %d\n",fst->key,lst->key,val);
		if (val<fst->key) return fst;
		if (val>lst->key) return NULL;
		for (listnode *it=fst;it!=lst;it=it->nxt) {
			if (it->key>=val) return it;
		}
		return lst;
	}

	long long query(int P,int Q,int U,int V) {
		long long gcd=0;
		for (listnode *it=fst;it!=lst;it=it->nxt) {
			if (it->key>=P&&it->key<=U) {
				//printf("node query %d: %d %d\n",it->key,Q,V);
				//node::print(it->val);
				//printf("\n");
				gcd=gcd2(gcd,node::query(it->val,Q,V));
				//printf("--> %lld\n",node::query(it->val,Q,V));
			}
		}
		if (lst->key>=P&&lst->key<=U) {
			gcd=gcd2(gcd,node::query(lst->val,Q,V));
		}
		return gcd;
	}
};

listnode* head;
int cnt;
int blk;
vector<cluster> cls;

queue<int> sq;

void init(int R, int C) {
	head=last;
	cnt=1;
	blk=1;
	cls.push_back(cluster(head));

	for (int i=2;i<150;i++) {
		sq.push(i*i);
	}
}

void update(int P, int Q, long long K) {
	//printf("update %d %d %lld\n",P,Q,K);
	//find which cluster
	int id=-1;
	for (int i=0;i<(int)cls.size();i++) {
		if (cls[i].lst->key<P) continue;
		id=i;
		break;
	}
	//printf("id %d %d %d\n",id,cls[id].fst->key,cls[id].lst->key);
	//check if R already exists
	listnode* curR=cls[id].find(P);
	//printf("curR %d\n",curR->key);
	//printf("%x\n",curR);
	if (curR!=NULL&&curR->key==P) {
		//exists
		//printf("exists\n");
		bool res = node::change(curR->val,{Q,P},K);
		node::change(cls[id].big,{Q,P},K);
		if (!res) {
			//C does not exist
			//printf("C not exist\n");
			node::insert(curR->val,new node({Q,P},K));
			node::insert(cls[id].big,new node({Q,P},K));
		}
	} else {
		//does not exist
		//printf("not exist\n");
		listnode* newR=new listnode(P);
		listnode::insert(curR,newR);	
		if (curR==cls[id].fst) cls[id].fst=newR;	
		cls[id].size++;	
		curR=newR;
		cnt++;
		//printf("curR %d\n",curR->key);
		//printf("id %d\n",id);
		
		//insert C in curR
		node::insert(curR->val,new node({Q,P},K));				
		//printf("yay\n");
		node::insert(cls[id].big,new node({Q,P},K));
		//printf("yay2\n");

		head=cls[0].fst;

		//if cnt is square, increase blk
		if (cnt==sq.front()) {
			//for (int i=0;i<(int)cls.size();i++) {
				//if (cls[i].big) delete cls[i].big;	
			//}	
			sq.pop();
			cls.clear();
			blk++;
			
			listnode *it=head;
			for (int i=0;i<blk;i++) {
				cls.push_back(cluster(it));
				//printf("%d---\n",i);
				node::insertFrom(cls[i].big,it->val);
				//node::print(it->val);
				//printf("\n");
				for (int j=1;j<blk;j++) {
					it=it->nxt;
					node::insertFrom(cls[i].big,it->val);
					//node::print(it->val);
					//printf("\n");
				}
				cls[i].size=blk;
				cls[i].lst=it;
				//printf("%d %d\n",cls[i].fst->key,cls[i].lst->key);
				it=it->nxt;
			}
			//return;
		} else {

			//adjust block
			int blkCnt=(int)cls.size();
			//printf("id %d blk %d\n",id,blkCnt);	
			for (int i=id;i<blkCnt;i++) {
				//printf("-- %d %d\n",i,cls[i].size);
				if (cls[i].size>blk) {
					//move lst to next cluster
					node::eraseFrom(cls[i].big,cls[i].lst->val);
					if (i==blkCnt-1) {
						cls.push_back(cluster(cls[i].lst));
						//printf("yay\n");
						assert(cls[i].lst==last);
					} else {
						node::insertFrom(cls[i+1].big,cls[i].lst->val);	
						cls[i+1].fst=cls[i+1].fst->prv;
						assert(cls[i+1].fst==cls[i].lst);
						cls[i+1].size++;
					}
					cls[i].lst=cls[i].lst->prv;
					cls[i].size--;
				}
			}
		}
	}

	//for (int i=0;i<(int)cls.size();i++) {
		//printf("%d --- %d\n",i,cls[i].size);
		//for (listnode *it=cls[i].fst;it!=cls[i].lst;it=it->nxt) {
			//node::print(it->val);
			//printf("\n");
		//}	
		//node::print(cls[i].lst->val);
		//printf("\n");
	//}

	//for (listnode* it=head;it!=last;it=it->nxt) {
		//printf("%d ",it->key);
	//}
	//printf("\n");
}


int cntt;
long long calculate(int P, int Q, int U, int V) {
	cntt++;
	//printf("ask %d %d %d %d\n",P,Q,U,V);
	long long gcd=0;
	//printf("-- %d cls\n",cls.size());
	stepcnt=0;
	int mx=0;
	for (int i=0;i<(int)cls.size();i++) {
		mx=max(mx,cls[i].size);
		if (P>cls[i].lst->key||U<cls[i].fst->key) continue;
		//printf("%d %d\n",cls[i].fst->key,cls[i].lst->key);
		if (P<=cls[i].fst->key&&cls[i].lst->key<=U) {
			//printf("yay\n");
			gcd=gcd2(gcd,node::query(cls[i].big,Q,V));
		} else {
			//printf("eiei\n");
			gcd=gcd2(gcd,cls[i].query(P,Q,U,V));
		}
	}
	if (cntt%10000==0) fprintf(stderr,"%d\n",cntt);
	//fprintf(stderr,"%d %d\n",cls.size(),mx);
	//if (cntt>200000) fprintf(stderr,"%d\n",stepcnt);
	//cerr << stepcnt << endl;
	return gcd;
}
