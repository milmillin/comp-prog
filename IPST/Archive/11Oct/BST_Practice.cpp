#include <cstdio>
#include <vector>

using namespace std;

typedef struct {
	int val,left,right;
} node;

vector<node> bst;

int main () {
	int n;
	scanf("%d",&n);
	int x;
	scanf("%d",&x);
	int cur;
	bst.push_back(node{x,-1,-1});
	printf("*\n");
	for (int i=1;i<n;i++) {
		scanf("%d",&x);
		cur=0;
		bst.push_back(node{x,-1,-1});
		while (true) {
			if (x<bst[cur].val) {
				if (bst[cur].left!=-1) {
					cur=bst[cur].left;
					printf("L");
				} else {
					bst[cur].left=bst.size()-1;
					printf("L*\n");
					break;
				}
			} else {
				if (bst[cur].right!=-1) {
					cur=bst[cur].right;
					printf("R");
				} else {
					bst[cur].right=bst.size()-1;
					printf("R*\n");
					break;				
				}
			}
		}
		
	}
	return 0;
}
