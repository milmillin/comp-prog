#include <cstdio>

using namespace std;

bool isHole[1000100];

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int x;
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		isHole[x]=true;
	}
	int y;
	int cur=1;
	if (isHole[cur]) {
		printf("%d\n",cur);
		return 0;
	}
	for (int i=0;i<k;i++) {
		scanf("%d%d",&x,&y);
		if (cur==x) cur=y;
		else if (cur==y) cur=x;
		if (isHole[cur]) {
			printf("%d\n",cur);
			return 0;
		}
	}
	printf("%d\n",cur);
	return 0;
}
