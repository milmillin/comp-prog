#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int tbl[3010][3010];
int mic[3010][3010];
int r,c,e;

int dp(int x,int y) {
	if (x<0||y<0||x>=r||y>=c) return -2e9;
	if (x==0&&y==0) return tbl[x][y];
	if (mic[x][y]!=-1) return mic[x][y];
	return mic[x][y]=tbl[x][y]+max(dp(x-1,y),dp(x,y-1));
}

int main () {
	scanf("%d%d%d",&r,&c,&e);
	int a,b;
	for (int i=0;i<e;i++) {
		scanf("%d%d",&a,&b);
		tbl[a][b]++;
	}
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(r-1,c-1));	
	return 0;
}
