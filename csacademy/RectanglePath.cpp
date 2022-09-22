#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int tbl[1010][1010];
int fir[1010][1010];
int sec[1010][1010];

int dis[1010][1010];
int di[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

struct point {
    int r,c,dis;
};

queue<point> q;

int main () {
    int r,c;
    scanf("%d%d",&r,&c);
    for (int i=0;i<r;i++) {
        for (int j=0;j<c;j++) {
            scanf("%d",&tbl[i][j]);
        }
    }
    int h,w,sr,sc,fr,fc;
    scanf("%d%d%d%d%d%d",&h,&w,&sr,&sc,&fr,&fc);
    
    for (int i=0;i<r;i++) {
        int sum=0;
        for (int j=0;j<w;j++) {
            sum+=tbl[i][j];
        }
        fir[i][0]=sum;
        for (int j=w;j<c;j++) {
            sum+=tbl[i][j];
            sum-=tbl[i][j-w];
            fir[i][j-w+1]=sum;
        }
    }
    for (int j=0;j<c-w+1;j++) {
        int sum=0;
        for (int i=0;i<h;i++) {
            sum+=fir[i][j];
        }
        sec[0][j]=sum;
        for (int i=h;i<r;i++) {
            sum+=fir[i][j];
            sum-=fir[i-h][j];
            sec[i-h+1][j]=sum;
        }
    }
    r=r-h+1;
    c=c-w+1;
	
	//for (int i=0;i<r;i++) {
		//for (int j=0;j<c;j++) {
			//printf("%d ",sec[i][j]);
		//}
		//printf("\n");
	//}

	sc--;
    sr--;
    fr--;
    fc--;
    
    memset(dis,63,sizeof(dis));
    q.push(point{sr,sc,0});
    int nowR,nowC,nowDis;
    int nextR,nextC;
    while (!q.empty()) {
        nowR=q.front().r;
        nowC=q.front().c;
        nowDis = q.front().dis;
        
        if (nowR==fr&&nowC==fc) {
            printf("%d\n",nowDis);
            return 0;
        }
        
        q.pop();
        for (int i=0;i<4;i++) {
            nextR = nowR+di[i][0];
            nextC = nowC+di[i][1];
            if (nextR<0||nextR>=r||nextC<0||nextC>=c) continue;
            if (sec[nextR][nextC]) continue;
            if (dis[nextR][nextC]<=nowDis+1) continue;
            dis[nextR][nextC]=nowDis+1;
            q.push(point{nextR,nextC,nowDis+1});
        }
    }
    return 0;
}
