#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


char tbl[60][60];
int lakeNum[60][60];
vector<pair<int,int> > lakeSize(300,make_pair(2e9,2e9));
bool isLake[300];
bool visit[60][60];
int di[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
vector<pair<int,int> > lake[300];
queue<pair<int,int> > q;

bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
    return a.second<b.second;
}

int main () {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            scanf(" %c",&tbl[i][j]);
        }
    }
    int curLake=0;
    int realLake=0;
    for (int i=1;i<n-1;i++) {
        for (int j=1;j<m-1;j++) {
            if (tbl[i][j]=='.'&&!visit[i][j]) {
                curLake++;
                isLake[curLake]=true;
                lakeSize[curLake].first=curLake;
                lakeSize[curLake].second=0;
                q.push(make_pair(i,j));

                int nowR,nowC,nextR,nextC;
                while (!q.empty()) {
                    nowR=q.front().first;
                    nowC=q.front().second;
                    q.pop();
                    visit[nowR][nowC]=true;
                    lakeNum[nowR][nowC]=curLake;
                    lakeSize[curLake].second++;
                    lake[curLake].push_back(make_pair(nowR,nowC));
                    for (int k=0;k<4;k++) {
                        nextR=nowR+di[k][0];
                        nextC=nowC+di[k][1];
                        if (nextR>=n-1||nextR<=0||nextC>=m-1||nextC<=0) {
                            if (tbl[nextR][nextC]=='.') isLake[curLake]=false;
                            continue;
                        }
                        if (visit[nextR][nextC]) continue;
                        if (tbl[nextR][nextC]!='.') continue;
                        q.push(make_pair(nextR,nextC));
                    }
                }
                if (isLake[curLake]) realLake++;
            }
        }
    }
    int destroy=realLake-k;

    sort(lakeSize.begin(),lakeSize.end(),cmp);

    //printf("%d\n",realLake);

    int cur=0;
    int chg=0;
    while (destroy) {
        int now = lakeSize[cur].first;
        //printf("%d\n",now);
        if (isLake[now]) {
            //printf("Yay\n");
            for (int i=0;i<lake[now].size();i++) {
                tbl[lake[now][i].first][lake[now][i].second]='*';
                chg++;
            }
            destroy--;
        }
        cur++;
    }
    printf("%d\n",chg);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            printf("%c",tbl[i][j]);
        }
        printf("\n");
    }
    return 0;
}
