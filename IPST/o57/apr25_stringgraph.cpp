#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct node {
	string x;
	int id;
	node *l,*r;

	node(): l(0),r(0) {}
};

string p;
int cur=0;
int mic[600][2010];

bool ask(node* x) {
	if (mic[x->id][cur]!=-1) return mic[x->id][cur];
	if (x->l) {
		if (ask(x->l)) return mic[x->id][cur]=true;
		return mic[x->id][cur]=ask(x->r);
	}
	for (auto i:x->x) {
		if (i==p[cur]) cur++;
		if (cur==p.size()) return mic[x->id][cur]=true;
	}
	return mic[x->id][cur]=false;
}

void f() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<node> nodes(n+m);
	int x,a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&x,&a,&b);
		nodes[x].l=&nodes[a];
		nodes[x].r=&nodes[b];
		nodes[x].id=x;
	}
	string y;
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		cin >> y;
		nodes[x].x=y;
		nodes[x].id=x;
	}
	int k;
	scanf("%d",&k);
	p.clear();
	cin >> p;	
	cur=0;
	memset(mic,-1,sizeof(mic));
	printf("%s\n",(ask(&nodes[k])?"YES":"NO"));
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
