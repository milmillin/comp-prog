#include <cstdio>

using namespace std;

int tbl[300100];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int ans=0;
	int cnt;
	for (int i=30;i>=0;i--) {
		ans|=(1<<i);
		cnt=0;
		for (int j=0;j<n;j++) {
			if ((ans&tbl[j])==ans) cnt++;
		}
		if (cnt<2) {
			ans^=(1<<i);
		}
	}
	printf("%d\n",ans);
	return 0;
}
