#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

struct vec {
	long long x,y;
	int id,num;
};

struct mat {
	long long r11,r12;
	long long r21,r22;

	mat inv() const {
		return mat {r22,-r21,-r12,r11};
	}
};

vec operator* (const mat &a,const vec &b) {
	return vec{a.r11*b.x+a.r12*b.y,a.r21*b.x+a.r22*b.y,b.id,b.num};
}

const int inf=0x3f3f3f3f;

struct node2 {
	int id,num;
	int lazy;
	node2 *l,*r;

	node2():id(-1),num(inf),lazy(0),l(0),r(0) {}

	void expand() {
		if (l) {
			l->lazy+=lazy;
			l->num+=lazy;	
		}		
		if (r) {
			r->lazy+=lazy;
			r->num+=lazy;
		}
		lazy=0;
	}

	void combine() {
		expand();
		num=inf;
		if (l) {
			if (l->num<num) {
				num=l->num;
				id=l->id;
			}
		}
		if (r) {
			if (r->num<num) {
				num=r->num;
				id=r->id;
			}
		}
	}
};

node2* insert2(node2* tmp,int l,int r,int y,int id,int num) {
	node2* cur=tmp;
	if (!cur) {
		cur=new node2();
	}
	cur->expand();
	if (l+1==r) {
		cur->id=id;
		cur->num=num;
		return cur;
	}
	int m=(l+r)>>1;
	if (y<m) cur->l=insert2(cur->l,l,m,y,id,num);
	else cur->r=insert2(cur->r,m,r,y,id,num);
	cur->combine();
	return cur;
}

void update2(node2* tmp,int l,int r,int ll,int num) {
	if (!tmp) return;
	if (ll>=r) return;
	tmp->expand();
	if (ll<=l) {
		tmp->lazy+=num;
		tmp->num+=num;
		return;
	}	
	int m=(l+r)>>1;
	update2(tmp->l,l,m,ll,num);
	update2(tmp->r,m,r,ll,num);
	tmp->combine();
}

vector<int> zero;
void findZero(node2* tmp,int l,int r) {
	if (!tmp) return;
	if (tmp->num!=0) return;
	tmp->expand();
	if (l+1==r) {
		zero.push_back(tmp->id);
	}
	int m=(l+r)>>1;
	findZero(tmp->l,l,m);
	findZero(tmp->r,m,r);
}

struct lazyArg {
	int yl,num;
};

int cntx=0,cnty=0;
struct node {
	node2* nd;
	node *l,*r;
	vector<lazyArg> lazy;

	void expand() {
		for (auto &la:lazy) {
			update2(nd,0,cnty,la.yl,la.num);
		}	
		if (l) l->lazy.insert(l->lazy.end(),lazy.begin(),lazy.end());
		if (r) r->lazy.insert(r->lazy.end(),lazy.begin(),lazy.end());
		lazy.clear();
	}

	node(): nd(0),l(0),r(0) {}
};


node* insert(node* tmp,int l,int r,int x,int y,int id,int num) {
	node* cur=tmp;
	if (!cur) {
		cur=new node();
	}
	cur->nd=insert2(cur->nd,0,cnty,y,id,num);
	if (l+1==r) {
		return cur;
	}
	int m=(l+r)>>1;
	if (x<m) cur->l=insert(cur->l,l,m,x,y,id,num);
	else cur->r=insert(cur->r,m,r,x,y,id,num);
	return cur;
}

void update(node* tmp,int l,int r,int xl,int yl,int num) {
	if (!tmp) return;
	if (xl>=r) return;
	tmp->expand();
	if (xl<=l) {
		tmp->lazy.push_back(lazyArg{yl,num});
		return;
	}	
	int m=(l+r)>>1;
	update(tmp->l,l,m,xl,yl,num);
	update(tmp->r,m,r,xl,yl,num);
}

void print2(node2* tmp,int l,int r) {
	if (!tmp) return;
	if (l+1==r) {
		printf("%d,%d ",tmp->id,tmp->num);
		return;
	}
	int m=(l+r)>>1;
	print2(tmp->l,l,m);
	print2(tmp->r,m,r);
}

void print(node* tmp,int l,int r) {
	if (!tmp) return;
	if (l+1==r) {
		print2(tmp->nd,0,cnty);
		printf("\n");
		return;
	}
	int m=(l+r)>>1;
	print(tmp->l,l,m);
	print(tmp->r,m,r);
}

int ans[200100];

int main () {
	int n;
	scanf("%d",&n);
	long long x1,y1,x2,y2;
	scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);	
	mat tr=mat{x1,x2,y1,y2};
	tr=tr.inv();	
	vector<vec> tbl;
	int x,y;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		tbl.push_back(tr*vec{x,y,i+1,0});
	}
	map<int,int> cmpx,cmpy;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i].num);
		cmpx[tbl[i].x];
		cmpy[tbl[i].y];
	}
	for (auto &i:cmpx) {
		i.second=cntx++;
	}	
	for (auto &i:cmpy) {
		i.second=cnty++;
	}
	node *root=0;
	for (int i=0;i<n;i++) {
		tbl[i].x=cmpx[tbl[i].x];
		tbl[i].y=cmpy[tbl[i].y];

		printf("%lld %lld\n",tbl[i].x,tbl[i].y);
		
		root=insert(root,0,cntx,tbl[i].x,tbl[i].y,tbl[i].id,tbl[i].num);
	}
	printf("----\n");
	print(root,0,cntx);
	printf("---\n");

	for (int i=0;i<n;i++) {
		if (ans[i]!=0) continue;	
		ans[i]=i+1;	

		insert(root,0,cntx,tbl[i].x,tbl[i].y,tbl[i].id,inf);
		update(root,0,cntx,tbl[i].x,tbl[i].y,-1);
	printf("----\n");
	print(root,0,cntx);
	printf("---\n");

		printf(":%d\n",i+1);
		while (true) {
			root->expand();
			zero.clear();
			findZero(root->nd,0,cnty);
			if (zero.empty()) break;
			for (auto l:zero) {
				printf("%d\n",i);
				ans[l-1]=i+1;
				insert(root,0,cntx,tbl[l-1].x,tbl[l-1].y,tbl[l-1].id,inf);
				update(root,0,cntx,tbl[l-1].x,tbl[l-1].y,-1);
			}
		}
	}
	for (int i=0;i<n;i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
