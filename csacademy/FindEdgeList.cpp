#include <cstdio>
#include <deque>

using namespace std;

deque<int> pth[100100];

int main () {
    int n;
    scanf("%d",&n);
    int a,b;
    for (int i=1;i<=n;i++) {
        scanf("%d",&a);
        for (int j=0;j<a;j++) {
            scanf("%d",&b);
            pth[i].push_back(b);
        }
    }
    bool change;
    while (true) {
        change=false;
        for (int i=1;i<=n;i++) {
            if (pth[i].size()==0) continue;
            if (pth[pth[i].front()].size()==0) continue;
            if (pth[pth[i].front()].front()==i) {
                printf("%d %d\n",i,pth[i].front());
                pth[pth[i].front()].pop_front();
                pth[i].pop_front();
                change=true;
            }
        }
        if (!change) break;
    }
    for (int i=1;i<=n;i++) {
        if (pth[i].size()) {
            printf("-1\n");
            return 0;
        }
    }
    return 0;
}
