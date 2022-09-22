#include <cstdio>

using namespace std;

int main () {
	int n,x,y,p1,p2;
	scanf("%d%d%d%d%d",&n,&x,&y,&p1,&p2);
	while (true) {
		int nn;
		scanf("%d",&nn);
		int ans=0;
		int xx;
		for (int i=0;i<nn;i++) {
			scanf("%d",&xx);
			if (xx==p1||xx==p2) ans^=y;
			else ans^=x;
		}
		printf("-- %d\n",ans);
	}
	return 0;
}
