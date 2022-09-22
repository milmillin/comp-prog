#include <cstdio>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	printf("%d %d\n",n,n*(n-1)/2);
	for (int i=1;i<=n;i++) {
		for (int j=i+1;j<=n;j++) {
			printf("%d %d 1\n",i,j);
		}
	}
	return 0;
}
