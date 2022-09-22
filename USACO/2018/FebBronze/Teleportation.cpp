#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main () {
	int a,b,x,y;
	freopen("teleport.in","r",stdin);
	freopen("teleport.out","w",stdout);
	scanf("%d%d%d%d",&a,&b,&x,&y);
	printf("%d\n",min(min(abs(a-b),abs(a-x)+abs(y-b)),abs(a-y)+abs(x-b)));
	return 0;
}
