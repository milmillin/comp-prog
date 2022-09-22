#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    int hgt, id;
} bot;

bool cmp (const bot &a, const bot &b) {
    return a.hgt<b.hgt;
}

int main () {
    int n,m;
    scanf("%d%d",&n,&m);
    vector<bot> bt(n);
    vector<bool> dest(n);
    vector<int> hh(n);
    for (int i=0;i<n;i++) {
        scanf("%d",&bt[i].hgt);
        hh[i]=bt[i].hgt;
        bt[i].id=i;
    }
    sort(bt.begin(),bt.end(),cmp);
//    for (int i=0;i<n;i++) {
//        printf("%d ",bt[i].hgt);
//    }
//    printf("\n");
    int hgt;
//    vector<bot>::iterator cur;
//    vector<bot>::iterator stp=bt.end();
    int stp = n-1;

    int cnt;
    for (int i=0;i<m;i++) {
        scanf("%d",&hgt);
        cnt=0;
        while (stp>=0&&bt[stp].hgt>hgt) {
            //printf("%d\n",stp);
            if (dest[bt[stp].id]) {
                stp--;
                continue;
            }
            cnt++;
            dest[bt[stp].id]=true;

            if (bt[stp].id&&hh[bt[stp].id-1]<=hgt&&!dest[bt[stp].id-1]) {
                cnt++;
                dest[bt[stp].id-1]=true;
            }

            if (bt[stp].id<n-1&&hh[bt[stp].id+1]<=hgt&&!dest[bt[stp].id+1]) {
                cnt++;
                dest[bt[stp].id+1]=true;
            }

            stp--;
        }
        printf("%d\n",cnt);
//        cur=upper_bound(bt.begin(),bt.end(),bot{hgt,0},cmp);
//        //if (cur>stp)
//        //printf("++%d,%d\n",cur->hgt,cur->id);
//        for (vector<bot>::iterator j=cur;j<stp;j++) {
//            //printf("---%d\n",j->hgt);
//            if (dest[j->id]) continue;
//            cnt++;
//            dest[j->id]=true;
//            if (j->id&&hh[j->id-1]<=hgt&&!dest[j->id-1]) {
//                cnt++;
//                dest[j->id-1]=true;
//            }
//            if (j->id<n-1&&hh[j->id+1]<=hgt&&!dest[j->id+1]) {
//                cnt++;
//                dest[j->id+1]=true;
//            }
//        }
//        printf("%d\n",cnt);
//        stp=cur;
    }

    return 0;
}
