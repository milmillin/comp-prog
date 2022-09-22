#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct edge{
	int idx,wgt;
};

struct ei {
	int idx;
	long long wgt;
	int lev,last;
};

bool operator< (const ei &a, const ei &b) {
	return a.wgt>b.wgt;
}

priority_queue<ei> q;
vector<edge> pth[100100];
bool isSpc[100100];
int id[100100];
int spc[20];
long long dis[100100][10];
bool visit[100100][10][11];

int poww[10]={1,2,4,8,16,32,64,128,256,512};

int main () {
	int n,m,l,k;)
	scanf("%d%d%d%d",&n,&m,&l,&k);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
	}
	for (int i=1;i<=l;i++) {
		scanf("%d",&a);
		spc[i]=a;
		id[a]=i;
		isSpc[a]=true;
	}
	memset(dis,127,sizeof(dis));
	//printf("%I64d\n",dis[0][0]);
	dis[1][0]=0;
	q.push(ei{1,0,0,0});
	int now,nowLev,nowLast;
	long long nowT;
	int nextt,wi;
	while (!q.empty()) {
		now=q.top().idx;
		nowT=q.top().wgt;
		nowLev=q.top().lev;
		nowLast=q.top().last;
		q.pop();
		//if (nowT>dis[now][nowLev]) continue;
		//printf("%d %d %I64d\n",now,nowLev,nowT);
		for (int i=0;i<pth[now].size();i++) {
			nextt=pth[now][i].idx;
			wi=pth[now][i].wgt/poww[nowLev];
			if (nowT+wi<dis[nextt][nowLev]) {
				dis[nextt][nowLev]=nowT+wi;
				q.push(ei{nextt,dis[nextt][nowLev],nowLev,nowLast});
			}
			if (nowLev<k&&isSpc[now]==true) {
				if (spc[nowLast]!=now) {
					if (nowT+wi/2<dis[nextt][nowLev+1]) {
						dis[nextt][nowLev+1]=nowT+wi/2;
						q.push(ei{nextt,dis[nextt][nowLev+1],nowLev+1,id[now]});
					}
				}
			}
		}
	}
	long long ans=1e17;
	//printf("%I64d\n",ans);
	for (int i=0;i<=k;i++) {
		//printf("%I64d\n",dis[n][i]);
		//for (int j=0;j<=l;j++) {
			ans=min(ans,dis[n][i]);	
		//}
	}
	printf("%I64d\n",ans);
	return 0;
}
