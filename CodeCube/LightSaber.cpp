#include <cstdio>
#include <algorithm>

using namespace std;

void print(int from,int to) {
	if (from<to) {
		for (int i=from;i<=to;i++) printf("%d ",i);
	} else {
		for (int i=from;i>=to;i--) printf("%d ",i);
	}
}

int n,lis,lds;
void recur(int left,int right,int inc,int dec) {
	//printf("%d %d\n",left,right);
	print(max(left,right-inc+1),right);
	right=max(left,right-inc+1)-1;
	if (min(left+dec-1,right)>left) {
		print(min(left+dec-1,right),left);
		left=min(left+dec-1,right)+1;
	}
	if (left>right) return;
	recur(left,right,inc-1,dec-1);
}

int main () {
	scanf("%d%d%d",&n,&lis,&lds);
	if (lis+lds>n+1) {
		printf("IMPOSSIBLE\n");
		return 0;
	}

	print(n-lis+1,n);
	print(lds-1,1);

	recur(lds,n-lis,lis-1,lds-1);
	printf("\n");
	return 0;
}
