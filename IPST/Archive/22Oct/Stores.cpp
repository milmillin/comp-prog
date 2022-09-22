#include <cstdio>
#include <algorithm>

using namespace std;

int a[1000100];
int b[1000100];

int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&a[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&b[i]);
	}
	int maxx=(1<<n)-1;
	double sumA,sumB;
	int cntA,cntB;
	double minn=2e9;
	for (int i=0;i<=maxx;i++) {
		sumA=0;
		sumB=0;
		cntA=0;
		cntB=0;
		for (int j=0;j<n;j++) {
			if ((1<<j)&i) {
				cntA++;
				sumA+=a[j];
			} else {
				cntB++;
				sumB+=b[j];
			}
		}
		minn=min(minn,sumA*(100-cntA)/100+sumB*(100-cntB)/100);
	}
	printf("%.2f\n",minn);
	return 0;
}
