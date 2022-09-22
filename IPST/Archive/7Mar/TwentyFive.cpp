#include <cstdio>
#include <vector>

using namespace std;

bool adj[400][400];
bool avail[400];

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<=n;i++) {
		scanf("%d",&a);
		for (int j=0;j<a;j++) {
			scanf("%d",&b);
			adj[i][b]=true;
			adj[b][i]=true;
		}
		avail[i]=true;
	}
	vector<int> ans;
	for (int i=1;i<=n;i++) {
		if (avail[i]) {
			for (int j=1;j<=n;j++) {
				avail[j]=avail[j]&&adj[i][j];
				//printf("%d %d\n",avail[j],adj[i][j]);
			}
			ans.push_back(i);
		}
	}
	printf("%d\n",ans.size());
	for (int i=0;i<(int)ans.size();i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
