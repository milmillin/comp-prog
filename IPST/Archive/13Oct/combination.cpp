#include <cstdio>

using namespace std;

int ncr(int n,int r) {
	int sum=1;
	for (int i=n;i>n-r;i--) {
		sum*=i;
	}
	for (int i=2;i<=r;i++) {
		sum/=i;
	}
	return sum;
}

bool mark[20];
int now;
int nn,n,k,l;

int get(int idx) {
	int cur=0;
	for (int i=now+1;i<=nn;i++) {
		//printf("++%d\n",i);
		if (mark[i]) continue;
		//printf("**%d\n",i);
		if (cur==idx) return i;
		cur++;
	}
}

int main () {
	
	scanf("%d%d%d",&n,&k,&l);
	nn=n;
	l--;
	now=1;
	while (k) {
		k--;
		//printf("%d %d %d\n",n-now,k,ncr(n-now,k));
		while (l>=ncr(n-now,k)) {
			l-=ncr(n-now,k);
			now++;
		}
		printf("%d ",now);
		now++;
	}
	printf("\n");
	return 0;
}
