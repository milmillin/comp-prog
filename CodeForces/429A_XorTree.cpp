#include <cstdio>
#include <vector>

using namespace std;

int init[100100];
int goal[100100];
vector<int> pth[100100];
bool visit[100100];
vector<int> ans;

void recur(int idx,int st1,int st2) {
	visit[idx]=true;
	if ((init[idx]^st1)!=goal[idx]) {
		ans.push_back(idx);
		for (int i=0;i<pth[idx].size();i++) {
			if (visit[pth[idx][i]]) continue;
			recur(pth[idx][i],st2,st1^1);
		}
	} else {
		for (int i=0;i<pth[idx].size();i++) {
			if (visit[pth[idx][i]]) continue;
			recur(pth[idx][i],st2,st1);
		}
	}
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&init[i]);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&goal[i]);
	}
	recur(1,0,0);
	printf("%d\n",ans.size());
	for (int i=0;i<ans.size();i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}
