#include <cstdio>
#include <queue>

using namespace std;

char tbl[50][50];
char rTbl[50][50];
int visit[50][50];

int di[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
queue<pair<int,int> > q;

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	
	for (int i=0;i<n;i++) {
		for (int j=0;j<m;j++) {
			scanf(" %c",&tbl[i][j]);
		}
	}
	for (int i=1;i<n;i++) {
		for (int j=1;j<m;j++) {
			if (tbl[i][j]=='.'&&tbl[i-1][j]=='.'&&tbl[i][j-1]=='.'&&tbl[i-1][j-1]=='.') rTbl[i][j]='.';
			else rTbl[i][j]='#';
			//printf("%c",rTbl[i][j]);
		}
		//printf("\n");
	}
	int nowR,nowC,nextR,nextC;
	for (int i=1;i<m;i++) {
		if (rTbl[1][i]=='#') continue;
		q.push(make_pair(1,i));
		visit[1][i]=i;
		while (!q.empty()) {
			nowR=q.front().first;
			nowC=q.front().second;
			q.pop();
			//printf("%d %d\n",nowR,nowC);
			if (nowR==n-1) {
				printf("yes\n");
				return 0;
			}
			for (int j=0;j<4;j++) {
				nextR=nowR+di[j][0];
				nextC=nowC+di[j][1];
				if (nextR<=0||nextR>=n||nextC<=0||nextC>=m) continue;
				if (visit[nextR][nextC]==i) continue;
				if (rTbl[nextR][nextC]=='#') continue;
				visit[nextR][nextC]=i;
				q.push(make_pair(nextR,nextC));
			}
		}
	}
	printf("no\n");
	return 0;
}
