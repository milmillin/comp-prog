#include <cstdio>
#include <algorithm>

using namespace std;

int ll[100100];
int rr[100100];

int main () {
	int n;
	scanf("%d",&n);
	int a,b,l,r;
	l=r=0;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&ll[i],&rr[i]);
		l+=ll[i];
		r+=rr[i];
	}
	int maxx=abs(l-r);
	int id=0;
	for (int i=0;i<n;i++) {
		int neww=abs((l-ll[i]+rr[i])-(r-rr[i]+ll[i]));
		if (neww>maxx) {
			maxx=neww;
			id=i+1;
		}
	}
	printf("%d\n",id);
	return 0;
}
