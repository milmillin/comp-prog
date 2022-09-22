#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int to[300100];
int indeg[300100];
int des[300100];
vector<int> pth[300100];
queue<int> q;

//void change(int id, int tobe) {
//    des[id]=tobe;
//    for (int i=0;i<pth[id].size();i++) {
//        if (indeg[pth[id][i]]==0) continue;
//        change(pth[id][i],tobe);
//    }
//}

void change(int id, int tobe) {
    vector<int> stk;
    stk.push_back(id);
    int now;
    while (!stk.empty()) {
        now = stk.back();
        stk.pop_back();
        des[now]=tobe;
        for (int i=0;i<pth[now].size();i++) {
            if (indeg[pth[now][i]]==0) continue;
            stk.push_back(pth[now][i]);
        }
    }
}

int main () {
    int n;
    scanf("%d",&n);
    int a,b;
    for (int i=1;i<=n;i++) {
        scanf("%d",&a);
        if (a==0) continue;
        to[i]=a;
        pth[a].push_back(i);
        indeg[i]++;
    }
    for (int i=1;i<=n;i++) {
        if (indeg[i]==0) q.push(i);
        des[i]=-1;
    }
    int now;
    while (!q.empty()) {
        now = q.front();
        q.pop();
        change(now,now);
    }
    int qs;
    scanf("%d",&qs);
    for (int i=0;i<qs;i++) {
        scanf("%d%d",&a,&b);
        if (a==1) {
            if (des[b]==-1) printf("Cycle\n");
            else printf("%d\n",des[b]);
        } else {
            indeg[b]--;
            change(b,b);
        }
    }
    return 0;
}
