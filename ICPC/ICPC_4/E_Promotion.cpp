#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	vector<int> tbl(n);
	long long sum=0;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		sum+=tbl[i];
	}
	sort(tbl.begin(),tbl.end());
	for (int i=n-x;i>=0;i-=x) {
		for (int j=0;j<x-y;j++) {
			sum-=tbl[i+j];
		}
	}
	printf("%lld\n",sum);
	return 0;
}
