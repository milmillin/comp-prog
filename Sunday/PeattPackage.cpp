#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
    int n,k;
    scanf("%d%d",&n,&k);
    vector<int> w(n);
    vector<int> c(n);
    vector<int> mark(100100,0);
    int lo=0,hi=0;
    for (int i=0;i<n;i++) {
        scanf("%d%d",&w[i],&c[i]);
        lo = max(lo,w[i]);
        hi +=w[i];
    }
    int mid;
    int cnt;
    int cur;

    int sec=1;

    while (lo<hi) {
        mid = (lo+hi)/2;
        cnt=1;
        cur=0;
        for (int i=0;i<n;i++) {
            //printf("+%d,%d\n",c[i],w[i]);
            if (mark[c[i]]==sec||cur+w[i]>mid) {
                cnt++;
                cur=0;
                sec++;
            }
            cur+=w[i];
            mark[c[i]]=sec;
        }
        if (cnt>k) {
            lo=mid+1;
        } else {
            hi=mid;
        }
        //printf("--%d %d\n",mid,cnt);
        sec++;
    }
    cnt=1;
    cur=0;
    for (int i=0;i<n;i++) {
        //printf("+%d,%d\n",c[i],w[i]);
        if (mark[c[i]]==sec||cur+w[i]>hi) {
            cnt++;
            cur=0;
            sec++;
        }
        cur+=w[i];
        mark[c[i]]=sec;
    }
    sec++;
    if (cnt>k) printf("-1\n");
    else printf("%d\n",hi);
}

int main () {
    int q;
    scanf("%d",&q);
    while (q--) {
        f();
    }
    return 0;
}
