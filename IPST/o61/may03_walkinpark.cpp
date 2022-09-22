#include <cstdio>
#include <cassert>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int dis[210][210];

int di[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

bool block[210][210];

struct tree {
	int r,c;
};

int dist(const tree &a, const tree &b) {
	return abs(a.r-b.r)+abs(a.c-b.c);
}

vector<tree> blk;
vector<tree> poi;

struct ei {
	tree x;
	int dis;
};

bool operator< (const ei &a, const ei &b) {
	return a.dis>b.dis;
}

void sub3(int q) {
	int a,b,c,d;
	for (int i=0;i<q;i++) {
		scanf("%d%d%d%d",&a,&b,&c,&d);
				
	}	
}


int main () {
	int n,k,q;
	scanf("%d%d%d",&n,&k,&q);
	int a,b,c,d;
	if (k==0) {
		for (int i=0;i<q;i++) {
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%d\n",abs(c-a)+abs(b-d));
		}
		return 0;
	}	
	assert(n<=200);
	for (int i=0;i<k;i++) {
		scanf("%d%d",&a,&b);
		block[a][b]=true;
		blk.push_back(tree{a,b});
	}

	for (int i=0;i<k;i++) {
		a=blk[i].r;
		b=blk[i].c;
		if (!block[a-1][b-1]) poi.push_back(tree{a-1,b-1});
		if (!block[a-1][b+1]) poi.push_back(tree{a-1,b+1});
		if (!block[a+1][b-1]) poi.push_back(tree{a+1,b-1});
		if (!block[a+1][b+1]) poi.push_back(tree{a+1,b+1});
	}

	queue<pair<int,int>> qq;

	if (q>300) {
		sub3(q);
		return 0;
	}

	for (int i=0;i<q;i++) {
		scanf("%d%d%d%d",&a,&b,&c,&d);
		memset(dis,63,sizeof(dis));
		dis[a][b]=0;
		qq.push({a,b});	
		int nextr,nextc;
		while (!qq.empty()) {
			auto now=qq.front();
			qq.pop();	
			for (int i=0;i<4;i++) {
				nextr=now.first+di[i][0];
				nextc=now.second+di[i][1];	
				if (nextr<=0||nextr>n||nextc<=0||nextc>n) continue;
				if (block[nextr][nextc]) continue;	
				if (dis[nextr][nextc]<=dis[now.first][now.second]+1) continue;
				dis[nextr][nextc]=dis[now.first][now.second]+1;
				qq.push({nextr,nextc});
			}
		}
		printf("%d\n",dis[c][d]);
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				printf("%d ",dis[i][j]);
			}
			printf("\n");
		}
	}	
	return 0;
}
