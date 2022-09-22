#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

struct point {
	int x,y;
};

int len(point a, point b) {
	return abs(a.x-b.x)+abs(a.y-b.y);
}

vector<point> tbl;
int dis[100][100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int x1,y1,x2,y2;
	for (int i=0;i<n;i++) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		tbl.push_back(point{x1,y1});
		tbl.push_back(point{x2,y2});
	}
	//memset(dis,63,sizeof(dis));
	//for (int i=0;i<(int)tbl.size();i+=2) {
		//dis[i][i+1]=0;
		//dis[i+1][i]=0;
	//}
	for (int i=0;i<(int)tbl.size();i++) {
		dis[i][i]=0;
		for (int j=i+1;j<(int)tbl.size();j++) {
			dis[i][j]=dis[j][i]=len(tbl[i],tbl[j]);
		}
		if (i%2==0) {
			dis[i][i+1]=dis[i+1][i]=0;
		}
	}
	for (int k=0;k<(int)tbl.size();k++) {
		for (int j=0;j<(int)tbl.size();j++) {
			for (int i=0;i<(int)tbl.size();i++) {
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for (int i=0;i<m;i++) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int ans=len(point{x1,y1},point{x2,y2});
		for (int j=0;j<(int)tbl.size();j++) {
			for (int k=0;k<(int)tbl.size();k++) {
				ans=min(ans,dis[j][k]+len(point{x1,y1},tbl[j])+len(point{x2,y2},tbl[k]));
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
