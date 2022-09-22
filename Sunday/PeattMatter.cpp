#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
    int n;
    scanf("%d",&n);
//    vector<mask> tbl(20200);
//    int x;
//    scanf("%d",&x);
//    x+=100;
//    tbl[x]=exp(0);
//    for (int i=1;i<n;i++) {
//        scanf("%d",&x);
//        x+=100;
//        for (int j=20100;j>=0;j--) {
//            if (!isZero(tbl[j])&&isZero(tbl[j]&exp(i))) {
//                tbl[j+x]=tbl[j]|exp(i);
//            }
//        }
//    }
//    vector<int> hlf;
//    for (int i=0;i<20100;i++) {
//        if (bitCnt(tbl[i])==n/2) hlf.push_back(i);
//    }
    vector<vector<bool> > visit(20010,vector<bool>(110,false));
    vector<int> mark[20010];
    vector<int> hlf;
    //vector<bool> hlfMrk(20010,false);
    int x;
    mark[0].push_back(0);
    visit[0][0]=true;
    int sum=0;
    for (int i=0;i<n;i++) {
        scanf("%d",&x);
        sum+=x;
        for (int j=20000;j>=0;j--) {
            //printf("%d %d\n",j,mark[j].size());
            int tmp = mark[j].size();
            for (int k=0;k<tmp;k++) {
                if (!visit[j+x+100][mark[j][k]+1]) {
                    mark[j+x+100].push_back(mark[j][k]+1);
                    visit[j+x+100][mark[j][k]+1]=true;
                }
                if (mark[j][k]+1==n/2) {
                    //if (!hlfMrk[j+x+100]) {
                    //printf("-%d %d %d\n",j,mark[j][k]+1,j+x+100);
                    hlf.push_back(j+x+100);
                    //    hlfMrk[j+x+100]=true;
                    //}
                }
            }
        }
    }
    //sort(hlf.begin(),hlf.end());
    int minn=2e9;
//    for (int i=0;i<hlf.size();i++) {
//        printf("%d\n",hlf[i]);
//    }
    for (int i=0;i<hlf.size();i++) {
        minn = min(minn,abs(sum-2*(hlf[i]-50*n)));
    }
    printf("%d\n",minn);
    //printf("Yay\n");
}

int main () {
    int q;
    scanf("%d",&q);
    while (q--) {
        f();
        //printf("yay");
    }
    return 0;
}
