#include <cstdio>
#include <algorithm>

using namespace std;

const int maxa=10000100;

int lps[maxa];
int mark[maxa];


int tbl[1000100];
int left[1000100];
int right[1000100];

int par[1000100];

bool solve(int l,int r,int p) {
	if (r<l) return true;
	int sz=r-l+1;
	int k;
	for (int i=0;i<sz;i++) {
		if (i%2==0) k=l+i/2;
		else k=r-i/2;
		if (left[k]<l&&right[k]>r) {
			par[k]=p;
			return solve(l,k-1,k)&&solve(k+1,r,k);
		}
	}
	return false;
}

int main () {
	for (int i=2;i<maxa;i+=2) {
		lps[i]=2;
	}
	for (int i=3;i<maxa;i+=2) {
		if (lps[i]) continue;
		lps[i]=i;
		for (int j=i*2;j<maxa;j+=i) {
			if (lps[j]) continue;
			lps[j]=i;
		}
	}

	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		int j=tbl[i];
		while (j>1) {
			left[i]=max(left[i],mark[lps[j]]);
			j/=lps[j];
		}

		j=tbl[i];
		while (j>1) {
			mark[lps[j]]=max(mark[lps[j]],i);
			j/=lps[j];
		}
	}

	for (int i=1;i<maxa;i++) mark[i]=n+1;

	for (int i=n;i>0;i--) {
		int j=tbl[i];
		right[i]=n+1;
		while (j>1) {
			right[i]=min(right[i],mark[lps[j]]);
			j/=lps[j];
		}
		j=tbl[i];
		while (j>1) {
			mark[lps[j]]=min(mark[lps[j]],i);
			j/=lps[j];
		}
	}

	if (solve(1,n,0)) {
		for (int i=1;i<=n;i++) {
			printf("%d ",par[i]);
		}
		printf("\n");
	} else {
		printf("impossible\n");
	}
	return 0;
}
