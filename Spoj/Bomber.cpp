#include <cstdio>
#include <algorithm>

using namespace std;

int main () {
	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		if (a>b) swap(a,b);
		if (a==2&&b==2||a==4&&b==4||a==4&&b==6||a==8&&b==12||a==10&&b==10) {
			printf("2\n");
		} else {
			printf("1\n");
		}
	}
	return 0;
}
