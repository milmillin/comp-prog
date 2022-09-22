#include <cstdio>
#include <vector>

using namespace std;

struct edge {
	int to,sz;
};

bool visit[100100];
vector<edge> pth[100100];
int sub[100100];
bool visit2[100100];
int n;

long long dfs(int now) {
	visit[now]=true;
	long long sum=0;
	int cnt=1;
	int par=-1;
	int tmp;
	for (int i=0;i<(int)pth[now].size();i++) {
		if (visit[pth[now][i].to]) {
			par=i;
			continue;
		}
		tmp=dfs(pth[now][i].to);
		cnt+=sub[pth[now][i].to];
		sum+=tmp+sub[pth[now][i].to];
		pth[now][i].sz=sub[pth[now][i].to];
	}
	if (par!=-1) pth[now][par].sz=n-cnt;
	sub[now]=cnt;
	return sum;
}

long long ans;

void opt(int now,long long avg) {
	ans=min(ans,avg);
	visit2[now]=true;
	for (int i=0;i<(int)pth[now].size();i++) {
		if (visit2[pth[now][i].to]) continue;
		opt(pth[now][i].to,avg-pth[now][i].sz*2ll+n);
	}
}

int main () {
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(edge{b,0});
		pth[b].push_back(edge{a,0});
	}
	ans=dfs(1);
	opt(1,ans);
	printf("%I64d\n",ans);
	return 0;
}
