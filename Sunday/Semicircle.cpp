#include <cstdio>
#include <vector>

using namespace std;

void f() {
    int n;
    scanf("%d",&n);
    vector<pair<int,int> >tbl(n);
    bool impos=false;
    int over;
    int cnt=0;
    for (int i=0;i<n;i++) {
        scanf("%d%d",&tbl[i].first,&tbl[i].second);
        if (impos) continue;
        over=0;
        for (int j=0;j<=i-1;j++) {
            printf("-%d %d\n",tbl[j].first,tbl[j].second);
            if (tbl[i].first<tbl[j].first&&tbl[i].second<tbl[j].second&&tbl[i].second>tbl[j].first) {
                over++;
                printf("11\n");
            } else if (tbl[i].first>tbl[j].first&&tbl[i].first<tbl[j].second&&tbl[i].second>tbl[j].second) {
                over++;
                printf("22\n");
            }
        }
        if (over==0) cnt++;
        else if (over!=1) {
            impos=true;
        }
    }
    if (impos) {
        printf("0\n");
        return;
    }
    int sum=1;
    for (int i=0;i<cnt;i++) {
        sum*=2;
        sum%=1001;
    }
    printf("%d\n",sum);
}

int main () {
    int q;
    scanf("%d",&q);
    while (q--) {
        f();
    }
    return 0;
}
