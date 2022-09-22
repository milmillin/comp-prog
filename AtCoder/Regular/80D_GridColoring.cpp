#include <cstdio>

using namespace std;

int tbl[10010];
int ans[110][110];

int main () {
	int h,w;
	scanf("%d%d",&h,&w);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int curr=0,curc=0;
	int di=1;
	for (int i=0;i<n;i++) {
		for (int j=0;j<tbl[i];j++) {
			//printf("%d %d\n",curr,curc);
			ans[curr][curc]=i+1;
			if (curr==h-1&&di==1) {
				di=-1;
				curc++;
			} else if (curr==0&&di==-1) {
				di=1;
				curc++;
			} else {
				curr+=di;
			}
		}
	}
	for (int i=0;i<h;i++) {
		for (int j=0;j<w;j++) {
			printf("%d ",ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
