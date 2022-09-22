#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> pth[50050];
vector<int> ans;
int indeg[50050];
queue<int> q;

int main () {
    int n,m;
    scanf("%d%d",&n,&m);
    int a,b;
    for (int i=0;i<m;i++) {
        scanf("%d%d",&a,&b);
        pth[b].push_back(a);
        indeg[a]++;
    }
    int x,y;
    for (int i=1;i<=n;i++) {
        if (indeg[i]==0) q.push(i);
        if (pth[i].size()) sort(pth[i].begin(),pth[i].end());
    }
    bool isDif=false;
    int now;
    while (!q.empty()) {
        //printf("%d\n",q.front());
        if (q.size()>1) {
            isDif=true;

            now =x=q.front();
            q.pop();

            y=q.front();
        } else {
            now=q.front();
            q.pop();
        }
        //now = x;
        //q.pop();
        ans.push_back(now);
        for (int i=0;i<pth[now].size();i++) {
            indeg[pth[now][i]]--;
            if (indeg[pth[now][i]]==0) q.push(pth[now][i]);
        }
    }

    if (ans.size()!=n) {
        printf("Never\n");
    } else {
        if (isDif) {
            printf("Different\n");
            for (int i=0;i<ans.size();i++) {
                if (ans[i]==x) {
                    printf("%d ",y);
                } else if (ans[i]==y) {
                    printf("%d ",x);
                } else {
                    printf("%d ",ans[i]);
                }
            }
            printf("\n");
        } else {
            printf("Same\n");
            for (int i=0;i<ans.size();i++) {
                printf("%d ",ans[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
