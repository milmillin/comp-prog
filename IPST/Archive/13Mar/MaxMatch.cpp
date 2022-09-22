#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct edge {
	int to,wgt;
	bool dis;
};

struct ee {
	int from,to,wgt;
};

vector<edge> pth[10100];
vector<ee> add;

bool visit[10100];
int dp[10100][2];
bool res[10100];

void dfs(int idx) {
	visit[idx]=true;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i].to]) {
			pth[idx][i].dis=true;
			continue;
		}
		dfs(pth[idx][i].to);
	}
}

void mic(int idx) {
	int ans=0;
	int mx=0;
	visit[idx]=true;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i].to]) continue;
		mic(pth[idx][i].to);
		if (res[pth[idx][i].to]) {
			int tmp=dp[pth[idx][i].to][0];
			ans+=tmp;
		} else {
			int tmp=dp[pth[idx][i].to][1];
			int tmp2=dp[pth[idx][i].to][0]+pth[idx][i].wgt;
			//int tmp=mic(pth[idx][i].to,1,idx);
			//int tmp2=mic(pth[idx][i].to,0,idx)+pth[idx][i].wgt;
			ans+=tmp;
			mx=max(mx,tmp2-tmp);
		}
	}
	dp[idx][0]=ans;
	dp[idx][1]=ans+mx;
	//if (st) return ans+mx;
	//return ans;
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	//if(k) return 0;
	int a,b,c;
	for (int i=1;i<n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c,false});
		pth[b].push_back(edge{a,c,false});
	}
	for (int i=0;i<k;i++) {
		scanf("%d%d%d",&a,&b,&c);
		add.push_back(ee{a,b,c});
	}
	
	int ans=0;
	int end=1<<k;
	bool brk;
	for (int i=0;i<end;i++) {
		memset(visit,0,sizeof(visit));
		memset(res,0,sizeof(res));
		int cur=0;
		brk=false;
		for (int j=0;j<k;j++) {
			if ((1<<j)&i) {
				if (res[add[j].from]||res[add[j].to]) {
					brk=true;
					break;
				}
				res[add[j].from]=true;
				res[add[j].to]=true;
				cur+=add[j].wgt;
			}
		}
		if (brk) continue;
		mic(1);
		ans=max(ans,dp[1][1]+cur);
	}
	printf("%d\n",ans);
	return 0;
}
