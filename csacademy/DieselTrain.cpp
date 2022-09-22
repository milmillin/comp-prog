#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    int d,l,n;
    scanf("%d%d%d",&d,&l,&n);
    vector<int> tbl;
    int x;
    for (int i=0;i<n;i++) {
        scanf("%d",&x);
        tbl.push_back(x);
    }
    tbl.push_back(0);
    tbl.push_back(d);
    sort(tbl.begin(),tbl.end());
    double ans=0;
    double cur;
    for (int i=1;i<tbl.size();i++) {
		//printf("%d ",tb[i]);
        if (tbl[i-1]+l>=tbl[i]) continue;
        cur = tbl[i]-tbl[i-1]-l;
        cur/=2;
        cur*=cur;
        ans+=cur;
    }
	//printf("\n");
    printf("%f\n",ans/d);
    return 0;
}
