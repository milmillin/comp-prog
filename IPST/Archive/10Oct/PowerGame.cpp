#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	vector<int> a(n);
	vector<int> b(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&a[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&b[i]);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());

//	for (int i=0;i<n;i++) {
//		printf("%d ",a[i]);
//	}
//	printf("\n");
//	for (int i=0;i<n;i++) {
//		printf("%d ",b[i]);
//	}
//	printf("\n");

	int cur=n-1;
	int ans=0;
	for (int i=n-1;i>=0;i--) {
		while (cur&&b[cur]>=a[i]) cur--;
		if (cur>=0&&b[cur]<a[i]) {
			//printf("%d %d\n",a[i],b[cur]);
			ans+=a[i];
			cur--;
		}
	}
	printf("%d\n",ans);
	return 0;
}
