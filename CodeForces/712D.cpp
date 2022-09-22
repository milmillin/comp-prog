#include <cstdio>

using namespace std;

long long dp[200][200100];
int a,b,k,t;

long long getWays(int diff) {
	if (diff>2*k) return 0;
	return 2*k-abs(diff);
}

int main () {
	
	scanf("%d%d%d%d",&a,&b,&k,&t);
	
	for (int i=0;i<200100;i++) {
		dp[0][i]=getDiff()
	}

	return 0;
}
