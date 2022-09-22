#include <cstdio>

using namespace std;

int npr(int n,int r) {
	int sum=1;
	for (int i=n;i>n-r;i--) {
		sum*=i;
	}
	return sum;
}

bool mark[20];
int nn,n,k,l;

int get(int idx) {
	int cur=0;
	for (int i=1;i<=nn;i++) {
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
	while (k) {
		n--;
		k--;
		int ans = get(l/npr(n,k));
		//printf("--%d ",l/npr(n,k));
		mark[ans]=true;
		printf("%d ",ans);
		l%=npr(n,k);
	}
	printf("\n");
	return 0;
}
