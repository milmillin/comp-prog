#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	vector<int> tbl(2*n);
	for (int i=0;i<2*n;i++) {
		scanf("%d",&tbl[i]);
	}
	sort(tbl.begin(),tbl.end());
	long long sum=0;
	for (int i=0;i<2*n;i+=2) {
		sum+=tbl[i];
	}
	printf("%lld\n",sum);
	return 0;
}
