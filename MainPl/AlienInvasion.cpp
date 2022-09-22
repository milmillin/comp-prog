#include <cstdio>
#include <algorithm>

using namespace std;

long long tbl[1000100];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%lld",&tbl[i]);
	}
	for (int i=2;i<=n;i++) {
		tbl[i]=max(tbl[i-1],tbl[i-2]+tbl[i]);
	}
	printf("%lld\n",tbl[n]);
	return 0;
}
