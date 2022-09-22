#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef struct {
    int to, time;
} edge;

typedef struct {
    int to, time, k;
} path;

bool operator< (const path &a, const path &b) {
    return a.time>b.time;
}

vector<edge> pth[5010];
priority_queue<path> q;
int dis[5010][200];

int main () {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for (int i=0;i<5010;i++) {
        for (int j=0;j<200;j++) {
            dis[i][j]=2e9;
        }
    }
    int a,b,c;
    for (int i=0;i<m;i++) {
        scanf("%d%d%d",&a,&b,&c);
        pth[a].push_back(edge{b,c});
        pth[b].push_back(edge{a,c});
    }
    dis[1][0]=0;
    q.push(path{1,0,0});

    int now,nowT,nowK;
    //int next,wgt;
    while (!q.empty()) {
        now = q.top().to;
        nowT = q.top().time;
        nowK = q.top().k;
        q.pop();
        //printf("%d %d %d\n",now,nowT,nowK);
        if (nowT>dis[now][nowK]) continue;
        if (now==n&&nowK==0) break;
        //dis[now][nowK]=nowT;
        for (int i=0;i<pth[now].size();i++) {
            if (nowT+pth[now][i].time<dis[pth[now][i].to][nowK]) {
                dis[pth[now][i].to][nowK]=nowT+pth[now][i].time;
                q.push(path{pth[now][i].to,nowT+pth[now][i].time,nowK});
            }
            if (nowK<k&&nowT+pth[now][i].time/2<dis[pth[now][i].to][nowK+1]) {
                dis[pth[now][i].to][nowK+1]=nowT+pth[now][i].time/2;
                q.push(path{pth[now][i].to,nowT+pth[now][i].time/2,nowK+1});
            }
        }
    }
    int minDis=2e9;
    for (int i=0;i<=k;i++) {
        minDis=min(minDis,dis[n][i]);
    }
    printf("%d\n%d\n%d\n",dis[n][0],minDis,dis[n][0]-minDis);
    return 0;
}
