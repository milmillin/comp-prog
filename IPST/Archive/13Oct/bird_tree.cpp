#include <cstdio>

using namespace std;

int main () {
	int q;
	scanf("%d",&q);
	int a,b;
	int newA,newB;
	while (q--) {
		scanf("%d/%d",&a,&b);
		while (a!=1||b!=1) {
			if (a<=b) {
				newA=b-a;
				newB=a;
				printf("L");
			} else {
				newA=b;
				newB=a-b;
				printf("R");
			}
			a=newA;
			b=newB;
		}
		printf("\n");
	}
	return 0;
}
