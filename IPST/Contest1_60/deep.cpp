#include <cstdio>
#include <vector>

using namespace std;

int s,a,b;

int dir() {
	int res = ((s&8)>>3);
	s=(s*a+b)%40507;
	return res;
}


struct line {
	vector<int> nodes;
	line *a;
	line *b;
	int query(int l) {
		//printf("-- %d\n",l);
		//for (auto &a: nodes) {
			//printf("%d ",a);
		//}
		//printf("\n");
		if (l>=nodes.size()) {
			int r=dir();
			if (r) {
				if (b==NULL) return nodes.back();
				return b->query(l-nodes.size());
			} else {
				if (a==NULL) return nodes.back();
				return a->query(l-nodes.size());
			}
		}
		return nodes[l];
	}
};

vector<int> pth[200100];

line *root;

void dfs(int idx,line *x) {
	x->nodes.push_back(idx);
	if (pth[idx].size()==2) {
		x->a=new line{};
		dfs(pth[idx][0],x->a);
		x->b=new line{};
		dfs(pth[idx][1],x->b);	
	} else if (pth[idx].size()==1) {
		dfs(pth[idx][0],x);
	}
	return;
}

int main () {
	int n,q;	
	scanf("%d%d",&n,&q);
	int x,y;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		if (x!=-1) pth[i].push_back(x);
		if (y!=-1) pth[i].push_back(y);
	}
	root=new line{};
	dfs(0,root);
	int l;
	for (int i=0;i<q;i++) {
		scanf("%d%d%d%d",&l,&s,&a,&b);
		printf("%d\n",root->query(l));
	}
	return 0;
}
