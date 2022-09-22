#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	vector<int> a(n),b(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&a[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&b[i]);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	int maxx=0;
	for (int i=0;i<n;i++) {
		maxx=max(maxx,min(a[i],b[n-i-1]));
	}
	printf("%d\n",maxx);
	return 0;
}
