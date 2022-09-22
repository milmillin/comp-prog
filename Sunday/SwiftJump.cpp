#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct {
    int x,y,a;
} tile;

vector<tile> tbl(300100);
vector<int> sx[100100];
vector<int> sy[100100];

bool sortX(int a, int b) {
   return tbl[a].x<tbl[b].x;
}

bool sortY(int a, int b) {
    return tbl[a].y<tbl[b].y;
}

int rgt[300100];
int top[300100];

int mic[300100][3];
bool visit[300100];
queue<int> q;

int main () {
    int n,b;
    scanf("%d%d",&n,&b);
    int x,y,a;

    for (int i=0;i<n;i++) {
        scanf("%d%d%d",&tbl[i].x,&tbl[i].y,&tbl[i].a);
        sx[tbl[i].y].push_back(i);
        sy[tbl[i].x].push_back(i);
        mic[i][0]=-2e9;
        mic[i][1]=-2e9;
        mic[i][2]=-2e9;
    }
    //printf("Yay\n");
    for (int i=0;i<100100;i++) {
        //printf("%d\n",i);
        if (sx[i].size()) {
            sort(sx[i].begin(),sx[i].end(),sortX);
            rgt[sx[i].back()]=-1;
            for (int j=sx[i].size()-2;j>=0;j--) {
                rgt[sx[i][j]]=sx[i][j+1];
            }
        }
        if (sy[i].size()) {
            sort(sy[i].begin(),sy[i].end(),sortY);

            top[sy[i].back()]=-1;
            for (int j=sy[i].size()-2;j>=0;j--) {
                top[sy[i][j]]=sy[i][j+1];
            }
        }
    }


    mic[0][0]=tbl[0].a;
    mic[0][1]=-2e9;
    mic[0][2]=-2e9;

    visit[0]=true;
    q.push(0);
    int now;
    while (!q.empty()) {
        now = q.front();
        q.pop();
        //printf("%d\n",now);

        if (top[now]!=-1 && max(mic[now][0],mic[now][2])>=b) mic[top[now]][0] = max(mic[top[now]][0],max(mic[now][0],mic[now][2])-b+tbl[top[now]].a);
        if (rgt[now]!=-1 && max(mic[now][0],mic[now][1])>=b) mic[rgt[now]][0] = max(mic[rgt[now]][0],max(mic[now][0],mic[now][1])-b+tbl[rgt[now]].a);

        if (top[now]!=-1) mic[top[now]][2] = max(mic[top[now]][2],max(mic[now][0],mic[now][2]));
        if (rgt[now]!=-1) mic[rgt[now]][1] = max(mic[rgt[now]][1],max(mic[now][0],mic[now][1]));

        if (!visit[top[now]]&&top[now]!=-1) q.push(top[now]);
        visit[top[now]]=true;
        if (!visit[rgt[now]]&&rgt[now]!=-1) q.push(rgt[now]);
        visit[rgt[now]]=true;
    }
//    for (int i=0;i<n;i++) {
//        printf("%d,%d,%d\n",mic[i][0],mic[i][1],mic[i][2]);
//    }
    printf("%d\n",mic[n-1][0]);
    return 0;
}
