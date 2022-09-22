#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[2000];

int main () {
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    int lo=0;
    for (int i=0;i<n;i++) {
        scanf("%d",&tbl[i]);
        lo=max(lo,tbl[i]);
    }
    int loss=2e9;
    int ans=-1;
    int cur=0;
    int curLoss=0;
    for (int w=lo;w<=b;w++) {
        cur=0;
        curLoss=0;
        for (int i=0;i<n;i++) {
            if (cur+tbl[i]>w) {
                curLoss+=w-cur;
                cur=tbl[i];
            } else {
                cur+=tbl[i];
            }
        }
        curLoss+=w-cur;
        if (curLoss<loss) {
            ans=w;
            loss=curLoss;
        }
    }
    printf("%d\n",ans);
    return 0;
}
