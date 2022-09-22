#include <cstdio>

using namespace std;

int tbl[100100];
int bit[200100];

int get(int idx) {
    int sum=0;
    while (idx) {
        sum+=bit[idx];
        idx-=idx&-idx;
    }
    return sum;
}

void update(int idx,int val ) {
    while (idx<200100) {
        bit[idx]+=val;
        idx+=idx&-idx;
    }
}

int main () {
    int n,a;
    scanf("%d%d",&n,&a);
    int x;
    for (int i=0;i<n;i++) {
        scanf("%d",&x);
        if (x>=a) tbl[i]=1;
        else tbl[i]=-1;
        if (i) tbl[i]+=tbl[i-1];
    }

//    for (int i=0;i<n;i++) {
//        printf("%d\n",tbl[i]);
//    }

    long long cnt=0;
    for (int i=n-1;i>=0;i--) {
        //printf("+%d\n",get(100001-tbl[i]));
        cnt+=get(100001-tbl[i]);
        update(100001-tbl[i],1);
    }
    cnt+=get(100001);
    printf("%lld\n",cnt);
    return 0;
}
