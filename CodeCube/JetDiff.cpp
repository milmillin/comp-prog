#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[200100];
int dp[2][120];
//int upb[200100];

int main () {
	int n;
	scanf("%d",&n);
	
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	//	if (i) ans+=abs(tbl[i]-tbl[i-1]);
	}
	
	int a;
	scanf("%d",&a);
	//ans*=a;
	//printf("%d\n",ans);
	
	for (int i=tbl[0];i<=100;i++) {
		dp[0][i]=(i-tbl[0])*(i-tbl[0]);
		//printf("%d ",dp[0][i]);	
	}
	//upb[0]=100;
	/*
	for (int i=1;i<tbl[0];i++) {
		dp[0][i]=2e9;
	}
	*/
	/*
	for (int i=0;i<=10;i++){
		printf("%d ",dp[0][i]);
	}
	printf("\n");
	*/
	//printf("yay");
	int ans;
	for (int i=1;i<n;i++) {
		ans=2e9;
		//printf("--%d\n",i);
		/*
		for (int j=1;j<tbl[i];j++) {
			dp[i%2][j]=2e9;
		}
		*/
		for (int j=tbl[i];j<=100;j++) {
			//printf("---%d\n",j);
			dp[i%2][j]=(j-tbl[i])*(j-tbl[i]);
			int minn=2e9;
			for (int k=tbl[i-1];k<=100;k++) {
				//printf("----%d\n",k);
				minn=min(minn,abs(j-k)*a+dp[(i-1)%2][k]);
				if (abs(j-k)*a+dp[(i-1)%2][k]>minn) break;
			}
			dp[i%2][j]+=minn;
			ans=min(ans,dp[i%2][j]);
			/*
			if (dp[i%2][j]>ans){
				upb[i]=j-1;
				break;
			}
			*/
			//printf("%d ",dp[i%2][j]);
		}
		/*
		for (int j=0;j<=10;j++) {
			printf("%d ",dp[i%2][j]);
		}
		printf("\n");
		*/
	}
	printf("%d\n",ans);

	/*
	for (int i=0;i<n;i++) {
		if (i==0) {
			if (tbl[i]>tbl[i+1]) continue;
			int x=a/2;
			int y=x*x-a*x;
			if (y<0&&tbl[i]+x<=100) {
				ans+=y;
				tbl[i]+=x;
			} else continue;
		} else if (i==n-1) {
			if (tbl[i]>tbl[i-1]) continue;
			int x=a/2;
			int y=x*x-a*x;
			if (y<0&&tbl[i]+x<=100) {
				ans+=y;
				tbl[i]+=x;
			} else continue;
		} else {
			
			if (tbl[i]<tbl[i-1]&&tbl[i]<tbl[i+1]) {
				int x=a;
				int y=x*x-2*a*x;
				if (y<0&&tbl[i]+x<=100) {
					ans+=y;
					tbl[i]+=x;
				} else continue;
			} else continue;
		}
		//printf("%d %d\n",i,ans);
	}
	*/
	//printf("%d\n",ans);
	return 0;
}
