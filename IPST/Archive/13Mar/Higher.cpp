#include <algorithm>
#include <cstdio>

using namespace std;

int tbl[1000100];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	int a,b;
	for (int i=0;i<k;i++) {
		scanf("%d%d",&a,&b);
		tbl[a]=b;
		int ans=n;
		for (int j=a+1;j<n;j++) {
			if (tbl[j]>b) {
				ans=min(j-a-1,ans);
				break;
			}
		}
		for (int j=a-1;j>=0;j--) {
			if (tbl[j]>b) {
				ans=min(a-j-1,ans);
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
