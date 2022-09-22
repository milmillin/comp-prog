#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int di[3][2]={{-1,0},{1,0},{0,1}};

struct pnt {
	int x,y,d,dis;
};

deque<pnt> q;

vector<vector<int> >turn[3];

int main () {
	int n,m,s;
	scanf("%d%d%d",&n,&m,&s);
	vector<vector<bool> >isWall(n,vector<bool>(m,false));
	char x;
	for (int i=0;i<n;i++) {
		for (int j=0;j<m;j++) {
			scanf(" %c",&x);
			if (x=='#') isWall[i][j]=true;
		}
	}
	//vector<vector<vector<int> > >turn(n,vector<vector<int> >(m,vector<int>(3,2e9)));
	for (int i=0;i<3;i++) turn[i].assign(n,vector<int>(m,2e9));
	q.push_back(pnt{s-1,0,2,0});
	q.push_back(pnt{s-1,0,1,1});
	q.push_back(pnt{s-1,0,0,1});
	int nextR,nextC,nextDis;
	int nowR,nowC,nowD,nowDis;
	int ans=2e9;
	while (!q.empty()){
		nowR=q.front().x;
		nowC=q.front().y;
		nowD=q.front().d;
		nowDis=q.front().dis;
		q.pop_front();
	//	printf("%d %d %d %d\n",nowR,nowC,nowD,nowDis);
		if (nowC==m-1) ans=min(ans,nowDis);
		if (nowDis>turn[nowD][nowR][nowC]) continue;
		for (int i=0;i<3;i++) {
			nextR=nowR+di[i][0];
			nextC=nowC+di[i][1];
			nextDis=nowDis+((i==nowD)?0:1);
			if ((i==0&&nowD==1)||(i==1&&nowD==0)) continue;
			if (nextR>=n||nextC>=m||nextR<0||nextC<0) continue;
			if (isWall[nextR][nextC]) continue;
			if (turn[i][nextR][nextC]<=nextDis) continue;
			turn[i][nextR][nextC]=nextDis;
			//printf("**%d %d %d %d\n",nextR,nextC,i,nextDis);
			if (i==nowD) q.push_front(pnt{nextR,nextC,i,nextDis});
			else q.push_back(pnt{nextR,nextC,i,nextDis});
		}
	}
	printf("%d\n",(ans==2e9)?-1:ans);
	return 0;
}
