#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

int main () {
	int x,y;
	scanf("%d%d",&x,&y);
	long long aa=max(abs(x),abs(y));
	long long bb=2*aa-1;
	
	if (y==aa) {
		//top;
		if (x>=1-aa) {
			printf("%lld\n",bb*bb+x+aa);
			return 0;
		}
	}

	if (x==aa) {
		printf("%lld\n",bb*bb+2*aa+aa-y);
		return 0;
	}
	
	if (y==-aa) {
		printf("%lld\n",bb*bb+2*aa+2*aa+aa-x);
		return 0;
	}

	if (x==-aa) {
		printf("%lld\n",bb*bb+2*aa+2*aa+2*aa+y+aa);
		return 0;
	}

	//printf("%lld\n",);
	return 0;
}
