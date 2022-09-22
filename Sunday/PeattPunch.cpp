#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    int val, id, ans;
} que;

bool operator< (const que &a, const que &b) {
    return a.val<b.val;
}

bool cmp (const que &a, const que &b) {
    return a.id<b.id;
}

typedef struct {
    int hgt,dx;
} bar;

int main () {
    int l,q;
    int x;
    scanf("%d%d",&l,&q);
    vector<int> inp(l);
    for (int i=0;i<l;i++) {
        scanf("%d",&inp[i]);
    }
    vector<que> qq(q);
    for (int i=0;i<q;i++) {
        scanf("%d",&qq[i].val);
        qq[i].id=i;
        qq[i].ans=0;
    }
    sort(qq.begin(),qq.end());

    vector<bar> stk;
    //stk.push_back(bar{0,0});
    //stk.push_back(bar{inp[0],0});
    for (int i=0;i<l;i++) {
        while (!stk.empty()&&inp[i]<stk.back().hgt) {
            //printf("-%d\n",inp[i]-stk.back()-1);
            stk.pop_back();
        }
        if (stk.empty()) {
            stk.push_back(bar{inp[i],0});
        } else {
            int req = max(inp[i]-stk.back().hgt,stk.back().dx);
            stk.push_back(bar{inp[i],req});

            vector<que>::iterator cur = upper_bound(qq.begin(),qq.end(),que{req-1,0,0});
            //printf("**%d\n",req);
            if (cur!=qq.begin()) {
                cur--;
                //printf("--%d\n",cur->val);
                cur->ans++;
            }
        }
//        for (int j=0;j<stk.size();j++) {
//            printf("%d ",stk[j]);
//        }
//        printf("\n");
    }

    int cur=0;
    for (int i=qq.size()-1;i>=0;i--) {
        cur+=qq[i].ans;
        qq[i].ans=cur;
        //printf("%d ",qq[i].val);
    }
    //printf("\n");
    sort(qq.begin(),qq.end(),cmp);
    for (int i=0;i<q;i++) {
        printf("%d\n",qq[i].ans);
    }
    return 0;
}
