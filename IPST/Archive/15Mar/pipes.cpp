#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> ys[300];
vector<int> re[300];
int st[300];
int endd[300];
int sum[300];
int cnt[300];

struct node {
	int val,cnt,ver;
	node *left,*right;
	node* insertN(int _val,int _cnt,int l, int r, int idx,int ver);
};

node *null = new node{0,0,-1,NULL,NULL};

node* node::insertN(int _val, int _cnt, int l, int r, int idx, int ver) {
	if (this->ver<ver) {
		if (l<=idx&&idx<r) {
			if (l+1==r) {
				return new node{_val,_cnt,ver,null,null};
			}
			int m=(l+r)>>1;
			return new node{this->val+_val,this->cnt+_cnt,ver,this->left->insertN(_val,_cnt,l,m,idx,ver),this->right->insertN(_val,_cnt,m,r,idx,ver)};
		}
	} else {
		this->val+=_val;
		this->cnt+=_cnt;
		if (l+1==r) return this;
		int m=(l+r)>>1;
		this->left=this->left->insertN(_val,_cnt,l,m,idx,ver);
		this->right=this->right->insertN(_val,_cnt,m,r,idx,ver);
	}
	return this;
}

void query(node* nd,int l,int r,int k, int &val,int &cnt) {
	if (k>=r-1) {
		val+=nd->val;
		cnt+=nd->cnt;
	} else if (k<l) return;
	else {
		int m=(l+r)>>1;
		query(nd->left,l,m,k,val,cnt);
		query(nd->right,m,r,k,val,cnt);
	}
}

int solve(node *nd, node *nd2, int l,int r,int ex,int &val,int &cnt) {
	//printf("%d %d %d %d\n",l,r,ex,nd->left->cnt-nd2->left->cnt);
	if (l+1==r) {
		val+=nd->val-nd2->val;
		cnt+=nd->cnt-nd2->cnt;
		return l;
	}
	int m=(l+r)>>1;
	if (nd->left->cnt-nd2->left->cnt<ex) {
		val+=nd->left->val-nd2->left->val;
		cnt+=nd->left->cnt-nd2->left->cnt;
		return solve(nd->right,nd2->right,m,r,ex-nd->left->cnt+nd2->left->cnt,val,cnt);
	} else {
		return solve(nd->left,nd2->left,l,m,ex,val,cnt);
	}
}

node* root[300];
int dp[300][300];

int main () {
	int n,m,w,h;
	scanf("%d%d%d%d",&n,&m,&w,&h);
	int x,y;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		ys[y].push_back(x);
	}
	int cur=0;
	for (int i=0;i<=200;) {
		while (ys[i].size()==0&&i<=200) {
			i++;
		}
		if (i<=200&&ys[i].size()) {
			cur++;
			st[cur]=i-1;
		}
		for (;i<=200&&ys[i].size();i++) {
			//printf("-%d %d\n",i,ys[i].size());
			re[cur].insert(re[cur].end(),ys[i].begin(),ys[i].end());
		}
		if (!endd[cur]) endd[cur]=i;
	}
	cur++;
	null->right=null;
	null->left=null;
	root[0]=null;
	//printf("yay\n");
	for (int i=1;i<cur;i++) {
		//printf("%d\n",i);
		root[i]=root[i-1]->insertN(re[i][0],1,-w,w+1,re[i][0],i);
		cnt[i]++;
		sum[i]+=re[i][0];
		for (int j=1;j<(int)re[i].size();j++) {
			root[i]->insertN(re[i][j],1,-w,w+1,re[i][j],i);
			cnt[i]++;
			sum[i]+=re[i][j];
		}
		
		cnt[i]+=cnt[i-1];
		sum[i]+=sum[i-1];
		//printf("%d %d\n",cnt[i],sum[i]);
	}
	int mSt=1,mEn=cur;
	if (st[0]==-1) mSt=2;
	if (endd[cur-1]>=h) mEn=cur-1;
	//base case j=0
	int lCnt,lSum;
	dp[0][0]=0;
	for (int i=1;i<cur;i++) {
		lCnt=lSum=0;
		query(root[i],-w,w+1,0,lSum,lCnt);
		dp[i][0]=sum[i]-2*lSum;
		//printf("%d %d %d %d\n",sum[i],lSum,i,dp[i][0]);
	}

	//dynamic
	int turnCnt=m/2-1;
	int coord;
	if (turnCnt<0) turnCnt=0;
	int rCnt,rSum;
	for (int j=1;j<=turnCnt;j++) {
		for (int i=mSt;i<mEn;i++) {
			dp[i][j]=2e9;
			for (int k=mSt-1;k<i;k++) {
				lCnt=lSum=0;
				coord=solve(root[i],root[k],-w,w+1,(cnt[i]-cnt[k]+1)/2,lSum,lCnt);
				rCnt=cnt[i]-cnt[k]-lCnt;
				rSum=sum[i]-sum[k]-lSum;
				dp[i][j]=min(dp[i][j],lCnt*coord-lSum+rSum-rCnt*coord+dp[k][j-1]);
			}
			//printf("%d ",dp[i][j]);
		}
		//printf("\n");
	}
	int ans=2e9;
	for (int i=mSt;i<mEn;i++) {
		ans=min(ans,dp[cur-1][0]-dp[i][0]+dp[i][turnCnt]);
	}
	printf("%d\n",ans);
	return 0;
}
