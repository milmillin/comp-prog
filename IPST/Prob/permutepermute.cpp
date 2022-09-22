#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct permute {
	int x[10];
	int& operator[](int idx) {
		return x[idx];
	}

	const int& operator[](int idx) const {
		return x[idx];
	}
	
	permute operator*(const permute &r) const {
		permute tmp;
		for (int i=0;i<10;i++) {
			tmp[i]=r[x[i]];
		}		
		return tmp;
	}
};

struct node {
	int key;
	int prior;
	permute psum;
	permute p;
	node *l,*r;
	node (int _key,permute _p) {
		key=_key;
		prior=(rand()<<16)^rand();
		p=_p;
		psum=_p;
		l=r=NULL;
	}
};

void update(node *x) {
	if (x==NULL) return;
	if (x->l!=NULL&&x->r!=NULL) x->psum=x->l->psum * x->p * x->r->psum;
	else if (x->l!=NULL||x->r!=NULL) x->psum=(x->l)?(x->l->psum * x->p):(x->p * x->r->psum);
	else x->psum=x->p;
	return;
}

void split(node *x,node* &l, node* &r,int key) {
	if (x==NULL) l=r=NULL;
	else if (x->key>key) {
		r=x;
		split(x->l,l,x->l,key);
	} else {
		l=x;
		split(x->r,x->r,r,key);
	}
	update(x);
}

void merge(node* &x,node *l, node*r) {
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

void insert(node* &x,node *tmp) {
	if (!x) x=tmp;
	else if (tmp->prior>x->prior) {
		split(x,tmp->l,tmp->r,tmp->key);
		x=tmp;
	} else {
		insert((x->key<tmp->key)?x->r:x->l,tmp);
	}
	update(x);
}

node* erase(node* &x, int key) {
	node* tmp=x;
	if (!x) return NULL;
	else if (x->key==key) {
		merge(x,x->l,x->r);
	} else {
		tmp=erase((x->key<key)?x->r:x->l,key);
	}
	update(x);
	return tmp;
}

int pos[100100];

int main () {
	srand(time(NULL));
	int n,m;
	scanf("%d%d",&n,&m);
	int x,b;
	node* root=NULL;
	for (int i=0;i<n;i++) {
		scanf("%d",&pos[i+1]);
		permute p;
		for (int j=0;j<10;j++) {
			scanf("%d",&p[j]);
		}
		node *tmp=new node(pos[i+1],p);
		insert(root,tmp);	
	}
	for (int i=0;i<m;i++) {
		scanf("%d%d",&x,&b);
		node *tmp=erase(root,pos[x]);
		tmp->l=tmp->r=NULL;
		pos[x]=b;
		tmp->key=pos[x];
		insert(root,tmp);
		printf("%d\n",root->psum[0]);
		//for (int j=0;j<10;j++) {
			//printf("%d ",root->psum[j]);
		//}
		//printf("\n");
	}
	return 0;
}
