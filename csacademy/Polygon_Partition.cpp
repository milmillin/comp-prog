#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int mod = 1000000007;

int mic1[200][200];
int mic2[200][200];
int s1[200][200];

int add(int a,int b) {
	if (a+b<mod) return a+b;
	return (a+b)%mod;
}

int mul(int a,int b) {
	return ((long long)a*b)%mod;
}

int dp2(int n,int k);
int dp1(int n,int k);

int sum1(int n,int k) {
	if (s1[n][k]!=-1) return s1[n][k];
	if (n==1) return 0;
	return s1[n][k]=add(dp1(n,k),sum1(n-1,k));
}

//no edge passing one
int dp1(int n,int k) {
	if (mic1[n][k]!=-1) return mic1[n][k];
	if (k==1) return 1;
	if (n<=3) return 0;

	mic1[n][k]=0;
	for (int i=3;i<n;i++) {
		for (int j=1;j<k;j++) {
			mic1[n][k]=add(mic1[n][k],mul(sum1(n-i+1,k-j),add(dp1(i,j),dp2(i,j))));
		}
	}
	return mic1[n][k];
}

//edge passing one
int dp2(int n,int k) {
	if (mic2[n][k]!=-1) return mic2[n][k];
	if (k==1) return 0;
	if (n==3) return 0;

	mic2[n][k]=0;
	

	for (int i=3;i<n;i++) {
		for (int j=1;j<k;j++) {
			mic2[n][k]=add(mic2[n][k],mul(dp1(i,j),add(dp1(n-i+2,k-j),dp2(n-i+2,k-j))));
		}
	}
	return mic2[n][k];
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	memset(mic1,-1,sizeof(mic1));
	memset(mic2,-1,sizeof(mic2));
	memset(s1,-1,sizeof(s1));
	for (int i=2;i<=n;i++) {
		for (int j=1;j<=k;j++) {
			dp1(i,j);
			dp2(i,j);
		}
	}
	printf("%d\n",add(dp1(n,k),dp2(n,k)));
	return 0;
}
