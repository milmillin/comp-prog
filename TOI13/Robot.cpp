#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct ei {
	int r,c;
};

vector<ei> st;
vector<ei> en;

bool isWall[2010][2010];
int dis[2010][2010];

int di[4][2]={{0,1},{0,-1},{-1,0},{1,0}};

queue<ei> q;

int main() {
	int r,c;
	scanf("%d%d",&r,&c);
	for (int i=0;i<r;i++) {
		char x;
		for (int j=0;j<c;j++) {
			scanf(" %c",&x);
			if (x=='W') isWall[i][j]=true;
			else if (x=='X') st.push_back(ei{i,j});
			else if (x=='A') en.push_back(ei{i,j});
		}
	}
	memset(dis,63,sizeof(dis));
	for (int i=0;i<(int)st.size();i++) {
		dis[st[i].r][st[i].c]=0;
		q.push(st[i]);
	}
	int nowr,nowc,nextc,nextr;
	while (!q.empty()) {
		nowr=q.front().r;
		nowc=q.front().c;
		q.pop();
		for (int i=0;i<4;i++) {
			nextc=nowc+di[i][0];
			nextr=nowr+di[i][1];
			if (nextc<0||nextc>=c||nextr<0||nextr>=r) continue;
			if (isWall[nextr][nextc]) continue;
			if (dis[nextr][nextc]<=dis[nowr][nowc]+1) continue;
			dis[nextr][nextc]=dis[nowr][nowc]+1;
			q.push(ei{nextr,nextc});
		}
	}
	int cnt=0;
	long long sum=0;
	for (int i=0;i<(int)en.size();i++) {
		if (dis[en[i].r][en[i].c]!=1061109567) {
			cnt++;
			sum+=dis[en[i].r][en[i].c];
		}
	}
	printf("%d %lld\n",cnt,sum*2);
	return 0;
}
