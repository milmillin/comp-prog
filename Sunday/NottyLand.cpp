#include <cstdio>
#include <vector>

using namespace std;

vector<int> pth[100100];
vector<int> rePth[100100];
vector<int> stk;
int grp[100100];
int grpNum=0;
int visit[100100];
int visit2[100100];

void recur(int idx) {
    visit[idx]=true;
    for (int i=0;i<pth[idx].size();i++) {
        if (visit[pth[idx][i]]) continue;
        recur(pth[idx][i]);
    }
    stk.push_back(idx);
}

void recur2(int idx) {
    visit2[idx]=true;
    grp[idx]=grpNum;
    for (int i=0;i<rePth[idx].size();i++) {
        if (visit2[rePth[idx][i]]) continue;
        recur2(rePth[idx][i]);
    }
}


int main () {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int d,x;
    for (int i=1;i<=n;i++) {
        scanf("%d",&d);
        for (int j=0;j<d;j++) {
            scanf("%d",&x);
            pth[i].push_back(x);
            rePth[x].push_back(i);
        }
    }
    for (int i=1;i<=n;i++) {
        if (visit[i]) continue;
        recur(i);
    }
    for (int i=n-1;i>=0;i--) {
        if (visit2[stk[i]]) continue;
        grpNum++;
        recur2(stk[i]);
    }
    int a,b;
    for (int i=0;i<k;i++) {
        scanf("%d%d",&a,&b);
        printf("%s\n",(grp[a]==grp[b])?"yes":"no");
    }
    return 0;
}
