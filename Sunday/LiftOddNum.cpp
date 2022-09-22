#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[300];
int mem[300][300][2];

int mic(int a,int b,int turn) {
    if (a>b) return 0;
    if (mem[a][b][turn]!=-1) return mem[a][b][turn];
    if (turn%2) {
        return mem[a][b][turn]=min(mic(a+1,b,(turn+1)%2),mic(a,b-1,(turn+1)%2));
    } else {
        return mem[a][b][turn]=max(tbl[a]%2+mic(a+1,b,(turn+1)%2),tbl[b]%2+mic(a,b-1,(turn+1)%2));
    }
}

int main () {
    memset(mem,-1,sizeof(mem));
    int n;
    scanf("%d",&n);
    int oddCnt=0;
    for (int i=0;i<n;i++) {
        scanf("%d",&tbl[i]);
        tbl[n+i]=tbl[i];
        if (tbl[i]%2) oddCnt++;
    }
    int cnt=0;
    for (int i=0;i<n;i++) {
        if ((mic(i,i+n-2,1)+tbl[i+n-1]%2)*2-oddCnt>0) cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
