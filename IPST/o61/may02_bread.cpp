#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

struct itv{ //inclusive
	int l,r;
};

bool operator< (const itv &a, const itv &b) {
	if (a.l!=b.l) return a.l<b.l;
	return a.r<b.r;
}

bool operator== (const itv &a, const itv &b) {
	return (a.l==b.l)&&(a.r==b.r);
}

struct node {
	itv key;
	int prior;
	vector<itv> flt;
	node *l,*r;
	
	node(itv _key): key(_key),prior((rand()<<16)^rand()),l(0),r(0) {
		flt.push_back(key);
	}	
};

void cpy(vector<itv> &out, const vector<itv> &in) {
	out.clear();
	for (auto &i:in) {
		out.push_back(i);
	}
}

void combine(vector<itv> &out, const vector<itv> &l, const vector<itv> &r) {
	out=l;
	//cpy(out,l);
	if (out.empty()) {
		assert(false);
		out=r;
		//cpy(out,r);
		return;
	}
	for (auto &i:r) {
		if (i.l>out.back().r) {
			out.push_back(i);
		} else if (i.r>out.back().r) {
			assert(i.l>=out.back().l);
			out.back().r=i.r;
		}
	}
}

void update(node *x) {
	if (!x) return;
	vector<itv> tmp;
	x->flt.clear();
	x->flt.push_back(x->key);
	if (x->l) combine(tmp,x->l->flt,x->flt);
	else tmp=x->flt;
	//else cpy(tmp,x->flt);
	if (x->r) combine(x->flt,tmp,x->r->flt);
	else x->flt=tmp;
	//else cpy(x->flt,tmp);
}

void split(node *x,node* &l, node* &r, itv key) {
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
		merge(x->r,x->r,r);
	} else {
		x=r;
		merge(x->l,l,x->l);
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

bool erase(node* &x,itv key) {
	bool res=false;
	if (!x) return false;
	if (x->key==key) {
		merge(x,x->l,x->r);
		res=true;
	} else {
		res=erase((x->key<key)?x->r:x->l,key);
	}
	update(x);
	return res;
}

long long cnt(node *x) {
	if (!x) return 0;
	long long ans=0;
	for (auto &i:x->flt) {
		ans+=i.r-i.l+1;
	}	
	return ans;
}

vector<int> raw_pos[100100];
vector<itv> pos[100100];
int cur[100100];
int tbl[100100];

int main () {
	int n;
	scanf("%d",&n);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		raw_pos[x].push_back(i);
		tbl[i]=x;
		assert(tbl[i]<n);
	}
	//printf("yay\n");
	for (int i=0;i<n;i++) {
		//printf("%d %d\n",i,raw_pos[i].size());
		for (int j=0;j<(int)raw_pos[i].size()-1;j++) {
			//printf("-- %d\n",j);
			pos[i].push_back(itv{raw_pos[i][j],raw_pos[i][j+1]-1});
		}
		if (!raw_pos[i].empty()) pos[i].push_back(itv{raw_pos[i].back(),n-1});
	}
	node* root=NULL;
	for (int i=0;i<n;i++) {
		cur[i]=4;
		if ((int)pos[i].size()>=5) {
			insert(root,new node(pos[i][cur[i]]));
		}		
	}	
	long long ans=0;
	for (int i=0;i<n;i++) {
		ans+=cnt(root);
		if (cur[tbl[i]]<(int)pos[tbl[i]].size()) {
			assert(erase(root,pos[tbl[i]][cur[tbl[i]]]));
		}
		cur[tbl[i]]++;
		if (cur[tbl[i]]<(int)pos[tbl[i]].size()) {
			insert(root,new node(pos[tbl[i]][cur[tbl[i]]]));
		}
		//add pos[tbl[i]][cur[tbl[i]]]
	}
	//assert(ans);
	printf("%lld\n",ans);
	return 0;
}
