#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[510][510];
int cnt[510][510];
int di[9][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};

pair<int,int> to[510][510];

int main() {
    int r,c;
    scanf("%d%d",&r,&c);
    memset(tbl,63,sizeof(tbl));
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            scanf("%d",&tbl[i][j]);
        }
    }
    int mn;
    pair<int,int> cur;
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            mn=2e9;
            for (int k=0;k<9;k++) {
                if (tbl[i+di[k][0]][j+di[k][1]]<mn) {
                    mn=tbl[i+di[k][0]][j+di[k][1]];
                    cur={i+di[k][0],j+di[k][1]};
                }
            }
            to[i][j]=cur;
        }
    }
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            while (to[i][j]!=to[to[i][j].first][to[i][j].second]) {
                to[i][j]=to[to[i][j].first][to[i][j].second];
            }
        }
    }
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            cnt[to[i][j].first][to[i][j].second]++;
        }
    }
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            printf("%d ",cnt[i][j]);
        }
        printf("\n");
    }
    return 0;
}
