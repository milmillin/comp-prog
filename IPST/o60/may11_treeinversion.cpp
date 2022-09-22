#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int val;
	int inv;
	int inv1;
	int inv2;
	vector<int> num;
	node *l,*r;
	node (int _val) {
		val=_val;
		inv=inv1=inv2=0;
		if (_val>0) num.push_back(_val);
		l=r=NULL;
	}	
};

node* nd[3000];
int chg[3000];
int n,k;

void build(node* x) {
	//printf("build %d\n",x->val);
	if (!x->l&&!x->r) return;
	build(x->l);
	build(x->r);
	for (auto i:x->l->num) {
		for (auto j:x->r->num) {
			if (i>j) x->inv1++;
			else x->inv2++;
		}
		x->num.push_back(i);
	}
	for (auto i:x->r->num) {
		x->num.push_back(i);
	}
	x->inv=x->inv1+x->l->inv+x->r->inv;
	chg[x->val+n]=x->inv2-x->inv1;
}

void print(node* x) {
	if (!x->l&&!x->r) {
		printf("%d ",x->val);
		return;
	}
	print(x->l);
	print(x->r);
}

int use[1000100];
bool mark[1000100];

int main () {
	scanf("%d%d",&n,&k);
	for (int i=-n+2;i<=n;i++) {
		nd[i+n]=new node(i);
	}
	int a,b,c;
	for (int i=1;i<n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		nd[a+n]->l=nd[b+n];
		nd[a+n]->r=nd[c+n];
	}
	build(nd[n]);
	memset(use,63,sizeof(use));
	vector<int> cur;
	int base=nd[n]->inv;
	cur.push_back(base);
	mark[base]=true;

	//for (int i=-n+2;i<=0;i++) {
		//printf("%d ",chg[i+n]);
	//}
	//printf("\n");

	for (int i=-n+2;i<=0;i++) {
		int tmp=cur.size();
		for (int k=0;k<tmp;k++) {
			int j=cur[k];
			if (!mark[j+chg[i+n]]) {
				mark[j+chg[i+n]]=true;
				cur.push_back(j+chg[i+n]);
				use[j+chg[i+n]]=i;	
			}
		}	
	}
	//printf("yay\n");

	vector<int> ans;
	while (k!=base) {
		//printf("%d %d\n",k,use[k]);
		ans.push_back(use[k]);
		k-=chg[use[k]+n];
	}
	printf("%d\n",ans.size());
	for (auto i:ans) printf("%d ",i);
	printf("\n");
	//print(nd[n]);
	//printf("\n");
	//printf("%d\n",nd[n]->inv);
	
	return 0;
}
