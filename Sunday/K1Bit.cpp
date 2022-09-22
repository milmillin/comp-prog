#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

long long mem[5000][30];

void init() {
    mem[0][0]=1;
    mem[1][0]=1;
    mem[1][1]=1;
    for (int i=2;i<5000;i++) {
        mem[i][0]=1;
        for (int j=1;j<=min(20,i);j++) {
            mem[i][j]=mem[i-1][j-1]+mem[i-1][j];
            //printf("%d ",mem[i][j]);
        }
        //printf("\n");
    }
}

long long ncr(int n,int r) {
    //if (mem[n][r]!=-1) return mem[n][r];
//    long long sum=1;
//    for (int i=r+1;i<=n;i++) {
//        sum*=i;
//    }
//    for (int i=2;i<=(n-r);i++) {
//        sum/=i;
//    }
//    if (sum!=mem[n][r]) printf("-%d %d %lld %lld-",n,r,sum,mem[n][r]);
    //return mem[n][r]=sum;
    if (r==1) return n;
    return mem[n][r];
}

int main () {
    int n,k;
    scanf("%d%d",&n,&k);

    if (k==1) {
        printf("1");
        for (int i=1;i<n;i++) {
            printf("0");
        }
        printf("\n");
        return 0;
    }

    init();
    long long sum=0;
    int dig=0;
//    for (int i=0;i<=k;i++) {
//        printf("%d\n",ncr(k-1+i,i));
//    }
    while (true) {
        if ((sum+ncr(k-1+dig,k-1))>=n) break;
        sum+=ncr(k-1+dig,k-1);
        //printf("%d\n",ncr(k-1+dig,k-1));
        dig++;
    }
    //printf("%d\n",dig);
    //printf("%d\n",dig);
    n-=sum+1;
    //printf("%d %d\n",sum,n);
    //printf("%d\n",n);
    printf("1");
    int one=k-1;
    int zero=dig;
    for (int i=0;i<dig+k-1;i++) {
        //printf("-%d\n",n);
        if (zero&&n<ncr(one+zero-1,one)) {
            //0..
            zero--;
            printf("0");
        } else {
            //1..
            n-=ncr(one+zero-1,one);
            one--;
            printf("1");
        }
    }
    return 0;
}
