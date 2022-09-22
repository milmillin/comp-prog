#include <cstdio>
#include <queue>

using namespace std;

//typedef struct {
//    int id,cost;
//} market;
//
////bool operator< (const market &a, const market &b) {
////    return a.cost>b.cost;
////}

priority_queue<int,vector<int>,greater<int> > qq;

int main () {
    int q;
    scanf("%d",&q);
    while (q--) {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        int x;
        for (int i=0;i<n;i++) {
            scanf("%d",&x);
            qq.push(x);
        }
        int a,b;
        int kk=0;
        for (int i=0;i<m;i++) {
            //printf("Yay\n");
            scanf("%d",&a);
            if (a==1) {
                scanf("%d",&b);
                qq.push(b-kk);
            } else if (a==2) {
                kk+=k;
            } else if (a==3) {
                if (!qq.empty()) qq.pop();
            }
        }
        long long cnt,tot;
        cnt=tot=0;
        while (!qq.empty()) {
            cnt++;
            tot+=qq.top()+kk;
            qq.pop();
        }
        printf("%lld %lld\n",cnt,tot);
    }
    return 0;
}
