#include "teams.h"
#include <vector>
#include <algorithm>

using namespace std;

struct student {
	int a,b;
};

bool operator< (const student &a, const student &b) {
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

struct node {
	int val;
	node *l,*r;
	node (int _val) {
		val=_val;
		l=r=NULL;
	}
};

node* insert(node* idx,int l,int r,int k,int val) {
	if (k<l||k>=r) return NULL;
	node* tmp = new node(0);
	if (l+1==r) {
		tmp->val=val+((idx)?idx->val:0);
		return tmp;
	}
	int m =(l+r)>>1;
	tmp->l=insert((idx)?idx->l:NULL,l,m,k,val);	
	tmp->r=insert((idx)?idx->r:NULL,m,r,k,val);
	tmp->val=((tmp->l)?tmp->l->val:0)+((tmp->r)?tmp->r->val:0);
	return tmp;
}

int n;
node* root[500100];
int 

void init(int N, int A[], int B[]) {
	n=N;
	vector<student> tbl;
	for (int i=0;i<n;i++) {
		tbl.push_back(student{A[i],B[i]});
	}
	sort(tbl.begin(),tbl.end());

}

int can(int M, int K[]) {
	return 0;
}
