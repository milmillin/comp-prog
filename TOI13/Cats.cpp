#include <cstdio>
#include <algorithm>


using namespace std;

int tbl[2000100];
int aa[2000100];

int main() {
	int n;
	scanf("%d",&n);
	int l=0;
	int r=0;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		r=max(r,tbl[i]);
	}

	int m;
	while (l<r) {
		m=(l+r)>>1;
		//printf("%d %d %d\n",m,l,r);
		//vector<int> aa;
		int cnt=0;
		for (int i=0;i<n;i++) {
			if (tbl[i]>m) aa[cnt++]=tbl[i]; 
		}
		bool work=true;
		for (int i=0;i<cnt;i+=2) {
			if (aa[i]!=aa[i+1]) {
				work=false;
				break;
			}
		}
		if (work) {
			r=m;
		} else {
			l=m+1;
		}
	}	
	printf("%d\n",r);
	return 0;
}
