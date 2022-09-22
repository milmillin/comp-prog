#include <cstdio>
#include <algorithm>

using namespace std;

int d[1010];
int s[1010];
int n;

double solve(double c) {
	double ans=0;
	for (int i=0;i<n;i++) {
		ans+=(double)d[i]/(s[i]+c);
	}
	return ans;
}

int main() {
	int t;
	scanf("%d%d",&n,&t);
	double lo=-2e9;
	double hi=10000000;	
	for (int i=0;i<n;i++) {
		scanf("%d%d",&d[i],&s[i]);
		lo=max(lo,-1.0*s[i]);
		//hi=max(hi,-1.0*s[i]);
	}
	
	double mid;
	while (hi-lo>1e-7) {
		mid=(lo+hi)/2.0;
//		printf("%f %f\n",mid,solve(mid));
		if (solve(mid)>t) {
			lo=mid;
		} else {
			hi=mid;
		}
	}
	printf("%.7f\n",lo);
	return 0;
}
