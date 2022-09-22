#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct p {
	int x,y;
};

vector<p> tbl;
int dis[2][2001][2];

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	int range=1000;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		tbl.push_back(p{a+range,b+range});
	}
	
	for (int i=0;i<=range*2;i++) {
		dis[0][i][0]=abs(i-range)+abs(tbl[0].y-range);
		dis[0][i][1]=abs(tbl[0].x-range)+abs(i-range);
		//printf("%d %d\n",dis[0][i][0],dis[0][i][1]);
	}
	//printf("--\n");
	int tt,ss;
	for (int i=1;i<n;i++) {
		for (int j=0;j<=range*2;j++) {
			tt=i%2;
			ss=(i-1)%2;
			dis[tt][j][0]=min(dis[ss][j][0]+abs(tbl[i].y-tbl[i-1].y),dis[ss][tbl[i].y][1]+abs(j-tbl[i-1].x));
			dis[tt][j][1]=min(dis[ss][j][1]+abs(tbl[i].x-tbl[i-1].x),dis[ss][tbl[i].x][0]+abs(j-tbl[i-1].y));
			//printf("%d %d\n",dis[i][j][0],dis[i][j][1]);
		}
		//printf("--\n");
	}
	int ans=2e9;
	int ei=(n-1)%2;
	for (int i=0;i<=range*2;i++) {
		ans=min(ans,min(dis[ei][i][0],dis[ei][i][1]));
		//printf("%d %d\n",dis[n-1][i][0],dis[n-1][i][1]);
	}
	printf("%d\n",ans);
	return 0;
}
