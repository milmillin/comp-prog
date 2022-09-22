#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int pth[1010][1010];

struct pt {
	int idx,ans;
};

queue<int> q;
bool visit[1010];
int ans[1010][2];
int sz[1010];

void inter(int idx,int val1,int val2) {
	int tmp1=-1;
	int tmp2=-1;
	if (val1==ans[idx][0]||val1==ans[idx][1]) tmp1=val1;
	if (val2==ans[idx][0]||val2==ans[idx][1]) tmp2=val2;
	ans[idx][0]=tmp1;
	ans[idx][1]=tmp2;
	if (ans[idx][0]==-1) swap(ans[idx][0],ans[idx][1]);
	if (ans[idx][1]==-1) sz[idx]=1;
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<k;i++) {
		for (int j=0;j<k;j++) {
			scanf("%d",&pth[i][j]);
		}
	}
	//todo chk k==1
	ans[0][0]=0;
	sz[0]=1;
	ans[1][0]=pth[0][1];
	sz[1]=1;
	//visit[1]=true;
	for (int i=2;i<k;i++) {
		ans[i][0]=pth[0][i];
		ans[i][1]=n-pth[0][i];
		sz[i]=2;
	}
	q.push(1);
	visit[1]=true;
	int now;
	long long nowPos;
	while (!q.empty()) {
		now=q.front();
		q.pop();
		nowPos=ans[now][0];
		//visit[now]=true;
		//printf("%d %d\n",now,nowPos);
		for (int i=1;i<k;i++) {
			if (visit[i]) continue;
			inter(i,(nowPos+pth[now][i])%n,(nowPos-pth[now][i]+n)%n);
			if (sz[i]) {
				visit[i]=true;
				q.push(i);
			}
		}
	}
	for (int i=0;i<k;i++) {
		printf("%d\n",ans[i][0]);
	}
	return 0;
}
