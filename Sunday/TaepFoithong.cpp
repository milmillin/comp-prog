#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

char mem[60000000];
bool visit[60000000];
int memPow[10][10];

int poww(int a,int b) {
    if (memPow[a][b]!=-1) return memPow[a][b];
    int sum=1;
    for (int i=0;i<b;i++) {
        sum*=a;
    }
    return memPow[a][b]=sum;
}

int q,k;

bool recur(int n) {
    if (mem[n]!=-1) return mem[n];
    //printf("-%d\n",n);
    visit[n]=true;
    int tmp=n;
    int sum=0;
    while (tmp) {
        sum+=poww(tmp%10,k);
        tmp/=10;
    }
    //printf("--%d\n",sum);
    if (sum==n) {
        return mem[n]=true;
    } else {
        if (visit[sum]==true&&mem[sum]==-1) return mem[n]=false;
        else return mem[n]=recur(sum);
    }
}

int main () {
    scanf("%d%d",&q,&k);
    char x[200];
    memset(memPow,-1,sizeof(memPow));
    memset(mem,-1,sizeof(mem));
    while(q--) {
        int sum=0;
        scanf("%s",x);
        for (int i=0;x[i]!=0;i++) {
            sum+=poww(x[i]-'0',k);
        }
        //printf("+%d\n",sum);
        printf("%s\n",(recur(sum))?"Yes":"No");
    }
    return 0;
}
