#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long tbl[100100];

struct line {
	long long m,c;
	int id;
	long long eval(long long x) {
		return m*x+c;
	}
};

bool bad(const line &a, const line &b, const line &c) {
	//return a-c is left to a-b
	return (b.c-a.c)*(a.m-c.m)>=(c.c-a.c)*(a.m-b.m);
}

long long dp[2][100100];
int par[210][100100];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) {
		scanf("%lld",&tbl[i]);
		tbl[i]+=tbl[i-1];
	}
	vector<line> stk;
	int cur,mn;
	line tmp;
	for (int j=1;j<=k;j++) {
		stk.clear();
		cur=j;
		mn=0;
		for (int i=j+1;i<=n;i++) {
			while (cur<i) {
				tmp.m=tbl[cur];
				tmp.c=dp[(j-1)%2][cur]-tbl[cur]*tbl[cur];
				tmp.id=cur;
				while (stk.size()>=2&&bad(stk[stk.size()-2],stk.back(),tmp)) stk.pop_back();
				stk.push_back(tmp);
				cur++;
			}	
			mn=min(mn,(int)stk.size()-1);
			while (mn+1<(int)stk.size()&&stk[mn+1].eval(tbl[i])>stk[mn].eval(tbl[i])) mn++;
			dp[j%2][i]=stk[mn].eval(tbl[i]);
			par[j][i]=stk[mn].id;
		}
	}						
	printf("%lld\n",dp[k%2][n]);
	int nn=n;
	for (int i=k;i>0;i--) {
		printf("%d ",par[i][nn]);
		nn=par[i][nn];	
	}
	printf("\n");
	return 0;
}
