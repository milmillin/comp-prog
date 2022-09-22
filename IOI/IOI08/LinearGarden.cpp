#include <cstdio>
#include <algorithm>

using namespace std;

int dp[1000100][3][3];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	dp[0][0][0]=1;
	dp[0][1][1]=1;
	dp[0][2][2]=1;
	for (int i=1;i<n;i++) {
		for (int j=0;j<3;j++) {
			dp[i][j][0]=dp[i-1][j][1];
			dp[i][j][1]=dp[i-1][j][0]+dp[i-1][j][2];
			dp[i][j][1]%=m;
			dp[i][j][2]=dp[i-1][j][1];
		}
	}
	for (int i=0;i<n;i++) {
		for (int j=0;j<3;j++) {
			dp[i][j][0]+=dp[i][j][1]+dp[i][j][2];
			dp[i][j][0]%=m;	
		}
	}
	char x;
	int mn=0;
	int mx=0;
	int cur=0;
	int ans=0;
	int nmx,nmn;
	for (int i=0;i<n;i++) {
		scanf(" %c",&x);
		if (x=='P') {
			cur++;
			nmx=max(mx,cur);
			nmn=min(mn,cur);
			
			if (nmx-nmn==1) {
				if (nmx==0) {
					ans+=dp[n-i-1][2+cur][0]+dp[n-i-1][1+cur][0];
				} else {
					ans+=dp[n-i-1][1+cur][0]+dp[n-i-1][0+cur][0];
				}	
				ans--;
			} else if (nmx-nmn==2) {
				ans+=dp[n-i-1][cur-nmn][0];	
			}
			ans%=m;
			cur-=2;
			mx=max(mx,cur);
			mn=min(mn,cur);
		} else {
			cur++;
			mx=max(mx,cur);
			mn=min(mn,cur);
		}			
	}
	ans++;
	ans%=m;
	printf("%d\n",(ans+m)%m);
	return 0;
}
