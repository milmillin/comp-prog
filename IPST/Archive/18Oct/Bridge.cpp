#include <cstdio>
#include <algorithm>

using namespace std;

int a[3010];
int b[3010];
int lcs[3010][3010];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&b[i]);
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			if (a[i]==b[j]) {
				lcs[i][j]=lcs[i-1][j-1]+1;
			} else {
				lcs[i][j]=max(lcs[i-1][j],lcs[i][j-1]);
			}
		}
	}
	printf("%d\n",lcs[n][n]);
	return 0;
}
