#include <cstdio>

using namespace std;

int n;

int e(int base,int p) {
	if (p==0) return 1;
	if (p==1) return base;
	if (p%2) {
		return (e(base,p-1)*base)%n;
	} else {
		int tmp=e(base,p/2);
		return (tmp*tmp)%n;
	}
}

int main () {
	while (true) {
		int x;
		scanf("%d",&x);
		printf("%c\n",x+'a'-1);
	}
	scanf("%d",&n);
	while (true) {
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",e(a,b));
	}
	return 0;
}
