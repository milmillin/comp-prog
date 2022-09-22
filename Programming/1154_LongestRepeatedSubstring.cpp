#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int mark[1000100];
long long tbl[20000];

long long pow(int n) {
    return tbl[n];
}
int n,k;
char x[20000];
int rnd[300];

void init() {
    tbl[0]=1;
    for (int i=1;i<20000;i++) {
        tbl[i]=tbl[i-1]*91;
        tbl[i]%=1000007;
    }

    for (int i=0;i<300;i++) {
        rnd[i]=rand()%10000000;
    }

}


int occ(int mid) {
    memset(mark,0,sizeof(mark));
    long long sum=0;
    int occur=0;
    for (int i=0;i<mid;i++) {
        sum*=91;
        sum%=1000007;
        sum+=rnd[x[i]];
        sum%=1000007;
    }
    mark[(sum+1000007)%1000007]++;
    occur=max(occur,mark[(sum+1000007)%1000007]);
    //printf("--%d\n",sum%1000007);
    for (int i=mid;i<n;i++) {
        sum-=pow(mid-1)*rnd[x[i-mid]];
        sum%=1000007;
        sum*=91;
        sum%=1000007;
        sum+=rnd[x[i]];
        sum%=1000007;
        mark[(sum+1000007)%1000007]++;
        occur=max(occur,mark[(sum+1000007)%1000007]);
        //printf("--%d\n",sum%1000007);
    }
    return occur;
}

int main () {
    init();
    scanf("%d%d",&n,&k);
    scanf("%s",x);


    int lo=0;
    int hi=n;

    long long sum;
    int mid;
    int occur;

    while (hi>lo) {
        mid=(lo+hi+1)/2;

        occur = occ(mid);

        if (occur>=k) {
            lo=mid;
        } else {
            hi=mid-1;
        }
        //printf("%d %d\n",mid,occur);
    }

    if (occ(lo+2)>=k) printf("%d\n",lo+2);
    else if (occ(lo+1)>=k) printf("%d\n",lo+1);
    else printf("%d\n",lo);
    return 0;
}
