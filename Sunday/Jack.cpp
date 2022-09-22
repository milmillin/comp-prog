#include <cstdio>
#include <vector>

using namespace std;

typedef struct  {
    int val,l,r;
} node;

vector<node> tree;

int main () {
    int n;
    scanf("%d",&n);
    int x;
    scanf("%d",&x);
    tree.push_back(node{x,-1,-1});
    printf("*\n");
    int cur;
    for (int i=1;i<n;i++) {
        scanf("%d",&x);
        tree.push_back(node{x,-1,-1});
        cur=0;
        while (true) {
            if (x>tree[cur].val) {
                printf("R");
                if (tree[cur].r==-1) {
                    tree[cur].r=i;
                    break;
                }
                cur = tree[cur].r;
            } else if (x<tree[cur].val) {
                printf("L");
                if (tree[cur].l==-1) {
                    tree[cur].l=i;
                    break;
                }
                cur = tree[cur].l;
            }
        }
        printf("*\n");
    }
    return 0;
}
