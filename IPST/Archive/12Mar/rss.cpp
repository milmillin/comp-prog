#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[20][100100];

struct ei{
	int id,rnk1,rnk2;	
};

bool cmp (const ei &a, const ei &b) {
	if (a.rnk1!=b.rnk1) return a.rnk1<b.rnk1;
	return a.rnk2<b.rnk2;
}

string x;

int get(int i,int j) {
	if (j>=(int)x.length()) return -1;
	return dp[i][j];
}

int suf[100100];

int lcp(int i,int j) {
	int ret=0;
	if (i==j) return x.length()-i;
	for (int k=19;k>=0 &&i<(int)x.length()&&j<(int)x.length();k--) {
		if (dp[k][i]==dp[k][j]) {
			i+=1<<k;
			j+=1<<k;
			ret+=1<<k;
		}
	}
	return ret;
}

int ans[100100];

struct bar{
	int val,w;
};

int main () {
	cin>>x;
	int n=x.length();
	for (int i=0;i<(int)x.length();i++) {
		dp[0][i]=x[i]-'a';
	}
	//dp[0][x.length()]=-1;
	for (int i=1;i<20;i++) {
		vector<ei> tmp;
		for (int j=0;j<(int)x.length();j++) {
			int a=dp[i-1][j];
			int b=get(i-1,j+(1<<(i-1)));
			tmp.push_back(ei{j,a,b});
		}
		sort(tmp.begin(),tmp.end(),cmp);
		for (int j=0;j<(int)tmp.size();j++) {
			if (j&&tmp[j].rnk1==tmp[j-1].rnk1&&tmp[j].rnk2==tmp[j-1].rnk2) {
				dp[i][tmp[j].id]=dp[i][tmp[j-1].id];
			} else {
				dp[i][tmp[j].id]=j;
			}
		}
		/*
		for (int j=0;j<(int)x.length();j++) {
			printf("%d ",dp[i][j]);
		}
		printf("\n");
		*/
	}
	for (int i=0;i<(int)x.length();i++) {
		suf[dp[19][i]]=i;
	}
	/*
	for (int i=0;i<(int)x.length();i++) {
		for (int j=suf[i];j<(int)x.length();j++) {
			printf("%c",x[j]);
		}
		printf(" %d\n",(i)?lcp(suf[i],suf[i-1]):0);
	}
	*/
	vector<bar> stk;
	for (int i=1;i<=n;i++) {
		int now=(i==n)?0:lcp(suf[i],suf[i-1]);
		int cur=0;
		while (!stk.empty()&&stk.back().val>now) {
			cur+=stk.back().w;
			ans[stk.back().val]=max(ans[stk.back().val],cur+1);
			stk.pop_back();
		}
		while (!stk.empty()&&stk.back().val==now) {
			cur+=stk.back().w;
			stk.pop_back();
		}
		cur++;
		stk.push_back(bar{now,cur});
	}
	for (int i=n-2;i>=1;i--) {
		ans[i]=max(ans[i],ans[i+1]);
	}
	/*
	for (int i=1;i<n;i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	*/
	int q;
	scanf("%d",&q);
	while (q--) {
		int xx;
		scanf("%d",&xx);
		printf("%d\n",(ans[xx])?ans[xx]:1);
	}
	return 0;
}
