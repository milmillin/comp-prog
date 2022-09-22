#include <cstdio>

using namespace std;

long long xorSum(long long n) {
	if (n%2) {
		if ((n/2)%2) {
			return 0;
		} else {
			return 1;
		}	
	} else {
		if ((n/2)%2) {
			return n+1;
		} else {
			return n;
		}
	}
}

int main () {
	int n;
	scanf("%d",&n);
	long long cur=0;
	long long a,b;
	for (int i=0;i<n;i++) {
		scanf("%I64d%I64d",&a,&b);
		cur^=xorSum(a+b-1)^xorSum(a-1);
	}
	//printf("%d\n",cur);
	printf("%s\n",(cur)?"tolik":"bolik");
	return 0;
}
