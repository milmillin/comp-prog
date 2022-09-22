#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct node {
	vector<bool> has;
	vector<int> vertex;
	pair<int,int> par;
	
	vector<node*> chd;

	node(int n): has(n,false) {}

	bool contain(int u,int v) {
		return has[u]&&has[v];	
	}

	~node() {
		for (auto i:chd) delete i;
	}
};

void f() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int> u;
	vector<int> v;
	u.reserve(m);
	v.reserve(m);
	for (int i=0;i<m;i++) {
		scanf("%d",&u[i]);
	}
	for (int i=0;i<m;i++) {
		scanf("%d",&v[i]);
	}
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
