#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> pth[100100];

int dfs(int idx,int par) {
	int ret=0;
	for (auto i:pth[idx]) {
		if (i==par) continue;
		ret=max(ret,dfs(i,idx)+1);
	}
	return ret;
}

int main () {
	freopen("newbarn.in","r",stdin);
	freopen("newbarn.out","w",stdout);
	int n;
	scanf("%d",&n);
	char x;
	int a;
	int cur=0;
	for (int i=0;i<n;i++) {
		scanf(" %c%d",&x,&a);
		if (x=='B') {
			cur++;
			if (a==-1) continue;
			pth[a].push_back(cur);
			pth[cur].push_back(a);
			//printf("add %d %d\n",a,cur);
		} else {
			printf("%d\n",dfs(a,a));
		}
	}
	return 0;
}
