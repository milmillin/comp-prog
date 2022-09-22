#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct node {
	int cnt;
	long long sum;

	node *l,*r;

	node():cnt(0),sum(0),l(0),r(0) {}
};

node* insert(node* tmp,int l,int r,int k) {
	node* cur=new node();
	if (tmp) {
		cur->l=tmp->l;
		cur->r=tmp->r;
		cur->cnt=tmp->cnt;
		cur->sum=tmp->sum;
	}
	if (l+1==r) {
		cur->cnt++;
		cur->sum+=k;
		return cur;
	}
		
	int m=(l+r)>>1;
	if (k<m) cur->l=insert(cur->l,l,m,k);
	else cur->r=insert(cur->r,m,r,k);
	cur->cnt=0;
	cur->sum=0;
	if (cur->l) {
		cur->cnt+=cur->l->cnt;
		cur->sum+=cur->l->sum;
	}
	if (cur->r) {
		cur->cnt+=cur->r->cnt;
		cur->sum+=cur->r->sum;
	}
	return cur;
}

struct qres {
	int cnt;
	long long sum;

	qres operator+ (const qres &b) const {
		return qres{cnt+b.cnt,sum+b.sum};
	}

	qres operator- (const qres &b) {
		return qres{cnt-b.cnt,sum-b.sum};
	}
};

qres query(node* cur,int l,int r,int ll,int rr) {
	if (!cur) return qres{0,0};
	if (ll>=r||rr<=l) return qres{0,0};
	if (ll<=l&&rr>=r) return qres{cur->cnt,cur->sum};
	int m=(l+r)>>1;
	return query(cur->l,l,m,ll,rr)+query(cur->r,m,r,ll,rr);
}

node* root[1000100];

int nxtx[100100];
int lastx[1000100];
long long dp[1000100];
pair<int,int> par[1000100];

const int maxy=1000005;

int main () {
	int n,m,g;
	scanf("%d%d%d",&n,&m,&g);
	int x1,y1,x2,y2;
	int w;
	for (int i=0;i<n;i+=2) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		w=x2;
		for (int x=x1+1;x<=x2;x++) {
			root[x]=insert(root[x-1],1,maxy,y1);
		}
	}
	vector<pair<int,int>> pts;
	pts.reserve(m);
	for (int i=0;i<m;i++) {
		scanf("%d%d",&x1,&y1);
		pts.push_back({x1,y1});
	}
	sort(pts.begin(),pts.end(),[](const pair<int,int> &a, const pair<int,int> &b) {
			return a.first>b.first;
			});
	memset(lastx,-1,sizeof(lastx));
	for (int i=0;i<m;i++) {
		nxtx[i]=lastx[pts[i].second];
		lastx[pts[i].second]=pts[i].first;
	}
	memset(dp,63,sizeof(dp));
	dp[w]=0;
	for (int i=0;i<m;i++) {
		if (nxtx[i]==-1) continue;
		qres gr=query(root[nxtx[i]],1,maxy,pts[i].second+1,maxy)-query(root[pts[i].first],1,maxy,pts[i].second+1,maxy);
		qres ls=query(root[nxtx[i]],1,maxy,1,pts[i].second)-query(root[pts[i].first],1,maxy,1,pts[i].second);
		long long cur=dp[nxtx[i]];
		if (g==1) {
			cur+=gr.cnt+ls.cnt;
		} else {
			cur+=gr.sum-(long long)pts[i].second*gr.cnt;
			cur+=(long long)pts[i].second*ls.cnt-ls.sum;
		}
		if (cur<dp[pts[i].first]) {
			dp[pts[i].first]=cur;
			par[pts[i].first]={nxtx[i],pts[i].second};
		}
	}
	int cur=0;
	vector<pair<int,int>> ans;
	while (cur!=w) {
		if (!ans.empty()&&par[cur].second==ans.back().second) {
			ans.pop_back();
		} else ans.push_back({cur,par[cur].second});
		ans.push_back({par[cur].first,par[cur].second});
		cur=par[cur].first;
	}
	printf("%lld\n",dp[0]);
	printf("%d\n",(int)ans.size());
	for (auto &i:ans) {
		printf("%d %d\n",i.first,i.second);
	}
	return 0;
}

