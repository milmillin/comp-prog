#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int,int> mp;
int a[600];
int b[600];
int mod=1000000007;
int dec[1010];

long long dp[600][1010];
long long q[1010][600];

long long inv[1010];

long long poww(long long x,int d) {
	if (d==0) return 1;
	if (d==1) return x;
	long long tmp=poww(x,d/2);
	tmp=tmp*tmp;
	tmp%=mod;
	if (d%2) return (tmp*x)%mod;
	return tmp;
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a[i],&b[i]);
		mp[a[i]-1];
		mp[b[i]];
	}
	int i=1;
	for (auto &ii:mp) {
		dec[i]=ii.first;
		ii.second=i++;
	}
	for (int i=0;i<n;i++) {
		a[i]=mp[a[i]-1];
		b[i]=mp[b[i]];
	}
	int nn=mp.size();

	for (int i=1;i<=n;i++) {
		inv[i]=poww(i,mod-2);
	}

	vector<int> rng;
	for (int i=0;i<n;i++) {
		for (int k=a[i]+1;k<=b[i];k++) {
			rng.push_back(dec[k]-dec[k-1]);
		}
	}
	rng.push_back(0);
	sort(rng.begin(),rng.end());
	rng.erase(unique(rng.begin(),rng.end()),rng.end());
	int val;	
	//printf("--- %d\n",rng.size());
	for (int k=1;k<(int)rng.size();k++) {
		val=rng[k];	
		q[k][0]=1;
		for (int j=1;j<=n;j++) {
			q[k][j]=q[k][j-1]*(val+j-1);
			q[k][j]%=mod;
			q[k][j]*=inv[j];
			q[k][j]%=mod;
			//printf("%lld ",q[k][j]);
		}
		//printf("\n");
	}	
	
	int kk;
	for (int i=0;i<n;i++) {
		//printf("** %d %d\n",a[i],b[i]);
		for (int k=a[i]+1;k<=b[i];k++) {
			int cnt=1;
			kk=lower_bound(rng.begin(),rng.end(),dec[k]-dec[k-1])-rng.begin();
			for (int j=i-1;j>=0;j--) {
				//printf("** %d %d %d %lld\n",i,j,k,dp[j][k-1]);
				dp[i][k]+=dp[j][k-1]*(q[kk][cnt]);
				//dp[i][k]+=dp[j][k-1]*(dec[k]-dec[k-1]);
				dp[i][k]%=mod;
				if (k>a[j]&&k<=b[j]) cnt++;
			}
			dp[i][k]+=q[kk][cnt];
			dp[i][k]+=dp[i][k-1];
			dp[i][k]%=mod;			
		}
		//for (int k=a[i]+1;k<=b[i];k++) {
			//dp[i][k]+=(dec[k]-dec[k-1]);
			//dp[i][k]+=dp[i][k-1];
			//dp[i][k]%=mod;
		//}
		for (int k=b[i]+1;k<=nn;k++) {
			dp[i][k]+=dp[i][k-1];
			dp[i][k]%=mod;
		}
		//for (int k=1;k<=nn;k++) {
			//printf("%lld ",dp[i][k]);
		//}
		//printf("\n");
	}
	long long ans=0;
	for (int i=0;i<n;i++) {
		ans+=dp[i][nn];
		ans%=mod;
	}
	ans+=mod;
	ans%=mod;
	printf("%lld\n",ans);
	return 0;
}
