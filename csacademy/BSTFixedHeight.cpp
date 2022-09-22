#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int mem[700][700][2];

int recur(int h,int n, bool st) {
    if (h==1&&n==1) return 1;
    if (h<10&&n>(1<<h)-1) return 0;
    if (st==0&&n==0) return 1;
    if (st&&n<h) return 0;
    
    if (mem[h][n][st]!=-1) return mem[h][n][st];
    
    long long sum=0;
    if (st) {
        for (int i=0;i<=n-1;i++) {
            sum+=recur(h-1,i,1)*recur(h-1,n-1-i,0);
            sum%=1000000007;
            sum+=recur(h-1,i,0)*recur(h-1,n-1-i,1);
            sum%=1000000007;
            sum-=recur(h-1,i,1)*recur(h-1,n-1-i,1);
            sum%=1000000007;
        }
    } else {
        for (int i=0;i<=n-1;i++) {
            sum+=recur(h-1,i,0)*recur(h-1,n-1-i,0);
            sum%=1000000007;
        }
    }
    //printf("%d %d %d %d\n",h,n,st,sum);
    return mem[h][n][st]=sum;
}

int main() {
    int h,n;
    scanf("%d%d",&n,&h);
    memset(mem,-1,sizeof(mem));
    printf("%d\n",recur(h,n,1));
    return 0;
}
