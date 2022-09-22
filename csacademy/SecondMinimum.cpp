#include <cstdio>
#include <queue>

using namespace std;

vector<int> ei[10100];

int main () {
    int n;
    scanf("%d",&n);
    queue<int> q;
    for (int i=1;i<=n;i++) {
        q.push(i);
    }
    int a,b,x;
    while (q.size()>1) {
        a = q.front();
        q.pop();
        b = q.front();
        q.pop();
        printf("Q %d %d\n",a,b);
        fflush(stdout);
        scanf("%d",&x);
        if (x==a) {
            ei[a].push_back(b);
        } else {
            ei[b].push_back(a);
        }
        q.push(x);
    }
    int mn = q.front();
    //printf("%d\n",mn);
    q.pop();
    for (int i=0;i<(int)ei[mn].size();i++) {
        q.push(ei[mn][i]);
		printf("%d\n",ei[mn][i]);
    }
    while (q.size()>1) {
        a=q.front();
        q.pop();
        a=q.front();
        q.pop();
        printf("Q %d %d\n",a,b);
        fflush(stdout);
        scanf("%d",&x);
        q.push(x);
    }
    printf("A %d\n",q.front());
    return 0;
}
