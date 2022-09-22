#include <cstdio>

using namespace std;

int d[400][400];
int deg[400];

int main () {
	int n,t;
	scanf("%d%d",&n,&t);
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			scanf("%d",&d[i][j]);
		}
	}
	bool isPth;
	int ans=0;
	int id=-1;
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if (i==j) continue;
			isPth=true;
			for (int k=0;k<n;k++) {
				if (k==i||k==j) continue;
				if (d[i][k]+d[k][j]==d[i][j]) {
					isPth=false;
					break;
				}
			}
			if (isPth) {
				deg[i]++;
				deg[j]++;
				//ans=max(ans,max(deg[i],deg[j]));
				if (deg[i]>ans) {
					ans=deg[i];
					id=i;
				}
				if (deg[j]>ans) {
					ans=deg[j];
					id=j;
				}
			}
		}
	}
	if (t==1) printf("%d\n",id+1);
	else printf("%d\n%d\n",id+1,ans/2);
	return 0;
}
