#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

//x-r y-c
typedef struct {
    int r,c,t;
} pee;

bool operator< (const pee &a, const pee &b) {
    return a.t>b.t;
}

int di[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

void f() {
    priority_queue<pee> q;
    int r,c,n,t,x,y;
    scanf("%d%d%d%d%d%d",&r,&c,&n,&t,&x,&y);
    vector<vector<bool> > tbl(r,vector<bool>(c));
    vector<vector<int> > dis(r,vector<int>(c,2e9));
    int tt,xx,yy;
    for (int i=0;i<n;i++) {
        scanf("%d%d%d",&tt,&xx,&yy);
        q.push(pee{xx,yy,tt});
        dis[xx][yy]=tt;
    }

    for (int i=0;i<r;i++) {
        for (int j=0;j<c;j++) {
            scanf(" %c",&xx);
            if (xx=='.') tbl[i][j]=false;
            else tbl[i][j]=true;
        }
    }
    int nowR,nowC,nowT;
    int nextR,nextC;
    while (!q.empty()) {
        nowR = q.top().r;
        nowC = q.top().c;
        nowT = q.top().t;
        q.pop();
        //printf("%d %d %d\n",nowR,nowC,nowT);
        //dis[nowR][nowC]=min(dis[nowR][nowC],nowT);
        //if (nowT>dis[nowR][nowC]) continue;
        //dis[nowR][nowC]=nowT;
        for (int i=0;i<4;i++) {
            nextR=nowR+di[i][0];
            nextC=nowC+di[i][1];
            if (nextR<0||nextR>=r||nextC<0||nextC>=c) continue;
            if (tbl[nextR][nextC]) continue;
            if (nowT+1>=dis[nextR][nextC]) continue;
            dis[nextR][nextC]=min(dis[nextR][nextC],nowT+1);
            q.push(pee{nextR,nextC,nowT+1});
        }
    }

//    for (int i=0;i<r;i++) {
//        for (int j=0;j<c;j++) {
//            printf("%d ",dis[i][j]);
//        }
//        printf("\n");
//    }
    vector<vector<bool> >visit(r,vector<bool>(c));
    queue<pee> qq;
    visit[x][y]=true;
    qq.push(pee{x,y,0});
    int maxT=-1;


    while (!qq.empty()) {
        nowR = qq.front().r;
        nowC = qq.front().c;
        nowT = qq.front().t;
        qq.pop();
        //if (nowT<dis[nowR][nowC]) {
            maxT=max(maxT,dis[nowR][nowC]-1);
        //}
        //else continue;
        if (nowT==t) {
            maxT=nowT;
            break;
        }
        for (int i=0;i<4;i++) {
            nextR=nowR+di[i][0];
            nextC=nowC+di[i][1];
            if (nextR<0||nextR>=r||nextC<0||nextC>=c) continue;
            if (tbl[nextR][nextC]) continue;
            if (nowT+1>=dis[nextR][nextC]) continue;
            if (visit[nextR][nextC]) continue;
            visit[nextR][nextC]=true;
            qq.push(pee{nextR,nextC,nowT+1});
        }
    }


    if (maxT>=t) {
        printf("YES\n");
    } else {
        printf("NO %d\n",maxT);
    }
    return;
}

int main () {
    int q;
    scanf("%d",&q);
    while (q--) {
        f();
    }
    return 0;
}
