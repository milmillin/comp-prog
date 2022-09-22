#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int p[100100];
vector<int> pth[100100];
int in[100100];
int out[100100];
int pre[100100];
int cur;

struct param {
	int idx;
	bool done;
};

vector<param> stk;

void dfs(int idx) {
	//printf("pre[cur] %d\n", idx);
	//printf("%d\n",dep);
	pre[cur]=idx;
	in[idx]=cur++;
	//if (idx==87005) printf("%d\n",pth[idx].size());
	for (int i=0;i<(int)pth[idx].size();i++) {
		dfs(pth[idx][i]);
	}
	out[idx]=cur-1;
}

struct node;

node* null;

struct node {
	int val;
	node *l,*r;
	node* insert(int l,int r,int w) {
		if (l<=w&&w<r) {
			if (l+1==r) {
				return new node{this->val+1,null,null};
			}
			int m=(l+r)>>1;
			return new node{this->val+1,this->l->insert(l,m,w),this->r->insert(m,r,w)};
		}
		return this;
	}
};

node* root[100100];

int query(node* idx,int l,int r, int ll,int rr) {
	if (rr<=l||ll>=r) return 0;
	if (ll<=l&&rr>=r) return idx->val;
	int m=(l+r)>>1;
	return query(idx->l,l,m,ll,rr)+query(idx->r,m,r,ll,rr);
}

map<int,int> mp;

int main () {
	freopen("promote.in","r",stdin);
	freopen("promote.out","w",stdout);
	null=new node{0,NULL,NULL};
	null->l=null->r=null;
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&p[i]);
		mp[p[i]];
	}
	int cnt=0;
	for (auto& val:mp) {
		val.second=cnt++;
	}
	for (int i=1;i<=n;i++) {
		p[i]=mp[p[i]];
		
	}
	int x;
	for (int i=2;i<=n;i++) {
		scanf("%d",&x);
		pth[x].push_back(i);
		//if (x==87005) printf("%d\n",pth[x][0]);
		//if (i==87005) printf("%d\n",x);
	}
	//printf("yay\n");
	stk.push_back(param{1,false});	
	while (!stk.empty()) {
		auto top=stk.back();
		auto idx=top.idx;
		//printf("%d\n",top.idx);
		if (top.done) {
			out[top.idx]=cur-1;
			stk.pop_back();
			continue;
		}
		stk.back().done=true;
		pre[cur]=idx;
		in[idx]=cur++;
		for (int i=0;i<(int)pth[idx].size();i++) {
			stk.push_back(param{pth[idx][i],false});
		}
	}
	//printf("yay]\n");
	for (int i=0;i<n;i++) {
		if (i==0) root[i]=null;
		else root[i]=root[i-1];
		//printf("insert %d\n",p[pre[i]]);
		root[i]=root[i]->insert(0,cnt,p[pre[i]]);
	}

	for (int i=1;i<=n;i++) {
		printf("%d\n",query(root[out[i]],0,cnt,p[i],cnt)-query(root[in[i]],0,cnt,p[i],cnt));
	}

	return 0;
}
