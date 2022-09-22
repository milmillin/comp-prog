#include <cstdio>
#include <vector>

using namespace std;

vector<int> pth[300100];
int par[300100];
vector<int> stk;

void recur (int n) {
    printf("%d ",n);
    for (int i=pth[n].size()-1;i>=0;i--) {
        recur(pth[n][i]);
    }
}

int main () {
    int n;
    scanf("%d",&n);
    int a,b;
    for (int i=1;i<=n;i++) {
        par[i]=i;
    }
    for (int i=1;i<n;i++) {
        scanf("%d%d",&a,&b);
        pth[b].push_back(a);
        par[a]=b;
    }
    int root=-1;
    for (int i=1;i<=n;i++) {
        if (par[i]==i) {
            root=i;
            break;
        }
    }
    //printf("%d\n",root);
    //recur(root);
    stk.push_back(root);
    int now;
    while (!stk.empty()) {
        now = stk.back();
        stk.pop_back();
        printf("%d ",now);
        for (int i=0;i<pth[now].size();i++) {
            stk.push_back(pth[now][i]);
        }
    }

    printf("\n");
    return 0;
}
