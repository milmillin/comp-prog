#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[1100];
long long mem[1100][100];
int n,k;

long long mic(int nn,int kk) {
    if (nn<0) return 0;
    if (mem[nn][kk]!=-1) return mem[nn][kk];
    long long minn=2e9;
    long long sum=0;
    for (int i=0;nn-i>=0;i++) {
        sum+=tbl[nn-i]*i;
        if (kk) minn = min(minn,sum+mic(nn-i-1,kk-1));
    }
    //printf("%d %d %d\n",nn,kk,sum);
    if (kk) minn = min(minn,mic(nn,kk-1));
    if (!kk) return mem[nn][kk]=sum;
    return mem[nn][kk]=minn;
}

int main () {
    memset(mem,-1,sizeof(mem));
    scanf("%d%d",&n,&k);
    for (int i=0;i<n;i++) {
        scanf("%d",&tbl[i]);
    }
//    for (int i=0;i<n;i++) {
//        for (int j=0;j<=k;j++) {
//            printf("%d ",mic(i,j));
//        }
//        printf("\n");
//    }
    printf("%lld\n",mic(n-1,k));
    return 0;
}
