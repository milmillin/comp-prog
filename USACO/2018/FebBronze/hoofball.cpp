#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

vector<int> tbl;
int indeg[1000];
bool visit[1000];
int to[1000];

void dfs(int idx) {
	visit[idx]=true;
	if (visit[to[idx]]) return;
	dfs(to[idx]);
}

int main () {
	freopen("hoofball.in","r",stdin);
	freopen("hoofball.out","w",stdout);
	int n;
	scanf("%d",&n);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		tbl.push_back(x);
	}
	if (n==2) {
		printf("1\n");
		return 0;
	}
	sort(tbl.begin(),tbl.end());
	to[0]=1;
	to[n-1]=n-2;
	indeg[1]++;
	indeg[n-2]++;
	for (int i=1;i<n-1;i++) {
		if (abs(tbl[i]-tbl[i-1])<=abs(tbl[i]-tbl[i+1])) {
			indeg[i-1]++;
			to[i]=i-1;
		} else {
			indeg[i+1]++;
			to[i]=i+1;
		}
	}
	int cnt=0;
	for (int i=0;i<n;i++) {
		if (indeg[i]==0) {
			cnt++;
			dfs(i);
		}
	}
	for (int i=0;i<n;i++) {
		if (!visit[i]) {
			dfs(i);
			cnt++;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
