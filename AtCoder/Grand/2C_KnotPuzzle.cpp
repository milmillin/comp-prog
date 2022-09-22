#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	long long val;
	node *left,*rgt;
	int cut;
	bool del;
};

struct ei {
	long long val;
	node *a,*b;
};

bool operator< (const ei &a ,const ei &b) {
	return a.val<b.val;
}

priority_queue<ei> q;

node* tbl[100100];
node* null;

int main () {
	int n,l;
	scanf("%d%d",&n,&l);
	long long x;
	null = new node{};
	null->left=null;
	null->rgt=null;
	for (int i=0;i<n;i++) {
		scanf("%lld",&x);
		tbl[i]=new node{x,null,null,i+1,false};
	}
	for (int i=0;i<n;i++) {
		if (i) tbl[i]->left=tbl[i-1];
		if (i<n-1) tbl[i]->rgt=tbl[i+1];
	}
	for (int i=0;i<n-1;i++) {
		q.push(ei{tbl[i]->val+tbl[i+1]->val,tbl[i],tbl[i+1]});
	}
	vector<int> ans;
	while (!q.empty()) {
		auto cur = q.top();
		q.pop();
		if (cur.val<l) continue;
		if (cur.a->del||cur.b->del) continue;
		node* now = new node {cur.a->val+cur.b->val,cur.a->left,cur.b->rgt,cur.b->cut,false};
		cur.a->del=true;
		cur.b->del=true;
		cur.a->left->rgt=now;
		cur.b->rgt->left=now;
		ans.push_back(cur.a->cut);
		q.push(ei{cur.a->left->val+now->val,cur.a->left,now});
		q.push(ei{cur.b->rgt->val+now->val,now,cur.b->rgt});
	}
	if (ans.size()<n-1) {
		printf("Impossible\n");
		return 0;
	}
	printf("Possible\n");
	for (int i=n-2;i>=0;i--) {
		printf("%d\n",ans[i]);
	}
	return 0;
}
