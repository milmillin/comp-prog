#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pth[100100];
int dep[100100];
int par[20][100100];

void dfs(int x,int p) {
    par[0][x]=p;
    dep[x]=dep[p]+1;
    for (auto i:pth[x]) {
        if (i==p) continue;
        dfs(i,x);
    }
}

int lca(int a,int b) {
    if (dep[a]<dep[b]) swap(a,b);
    int dif=dep[a]-dep[b];
    for (int i=0;i<20;i++) {
        if ((1<<i)&dif) {
            a=par[i][a];
        }
    }
    if (a==b) return a;
    for (int i=19;i>=0;i--) {
        if (par[i][a]!=par[i][b]) {
            a=par[i][a];
            b=par[i][b];
        }
    }
    return par[0][a];
}

bool mark[100100];

int main () {
    int n,m;
    scanf("%d%d",&n,&m);
    int a,b;
    for (int i=0;i<n-1;i++) {
        scanf("%d%d",&a,&b);
        pth[a].push_back(b);
        pth[b].push_back(a);
    }
    dfs(1,1);
    for (int i=0;i<20;i++) {
        for (int j=1;j<=n;j++) {
            par[i][j]=par[i-1][par[i-1][j]];
        }
    }
    printf("uau\n");
    for (int i=0;i<m;i++) {
        scanf("%d%d",&a,&b);
        mark[lca(a,b)]=true;
    } 
    int cnt=0;
    for (int i=1;i<=n;i++) {
        if (mark[i]) cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
