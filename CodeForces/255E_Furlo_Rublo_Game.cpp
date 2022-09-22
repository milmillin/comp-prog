#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);

	long long x;
	int ans=0;
	for (int i=0;i<n;i++) {
		scanf("%I64d",&x);
		if (x<4) ans^=0;
		else if (x<16) ans^=1;
		else if (x<82) ans^=2;
		else if (x<6724) ans^=0;
		else if (x<50626) ans^=3;
		else if (x<2562991876ll) ans^=1;
		else ans^=2;
	}
	if (ans) printf("Furlo\n");
	else printf("Rublo\n");
	return 0;
}
