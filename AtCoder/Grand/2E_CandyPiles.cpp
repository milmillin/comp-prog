#include <cstdio>
#include <algorithm>

using namespace std;

long long tbl[100100];

int main () {
	int n;
	scanf("%d",&n);
	long long cur=0;
	long long mx=0;
	long long cur2=0;
	for (int i=0;i<n;i++) {
		scanf("%lld",&tbl[i]);
		cur^=(tbl[i])%2;
		cur2^=(tbl[i]+1)%2;
		printf("%lld\n",(tbl[i])%2);
		mx=max(mx,tbl[i]);
	}
	if (cur==0) {
		printf("First1\n");
		return 0;
	}
	for (int i=0;i<n;i++) {
		if (tbl[i]==mx) {
			cur2^=(tbl[i]+1)%2;
			if (cur2==0) {
				printf("First2\n");
				return 0;
			} else break;
		}
	}
	printf("Second\n");
	return 0;
}
