#include <cstdio>
#include <algorithm>
#include <queue>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

struct ei {
	int to;
	unsigned long long wgt;
	int st;
};

bool operator< (const ei &a, const ei &b) {
	return a.wgt>b.wgt;
}

vector<ei> pth[100100];

unsigned long long dis[1010][2];

void printbin(unsigned long long x) {
	for (int i=63;i>=0;i--) {
		if ((x&(1llu<<i))) {
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n");
}

int main () {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	assert(q<=1000);
	int a,b;
	unsigned long long c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%llu",&a,&b,&c);
		pth[a].push_back(ei{b,c,0});
		pth[b].push_back(ei{a,c,0});
		assert(c<=1);
	}
	unsigned long long inf=(((1llu<<63)-1)<<1)^1;
	priority_queue<ei> qq;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
			memset(dis,255,sizeof(dis));		
			dis[a][0]=0;
			qq.push(ei{a,dis[a][0],0});
			while (!qq.empty()) {
				auto now=qq.top();
				qq.pop();
				for (auto &k:pth[now.to]) {
					if (now.wgt^k.wgt) {
						//goto st 1
						if (dis[k.to][1]<=(dis[now.to][now.st]^k.wgt)) continue;
						dis[k.to][1]=(dis[now.to][now.st]^k.wgt);
						qq.push(ei{k.to,dis[k.to][1],1});
					} else {
						//goto st 0
						if (dis[k.to][0]<=(dis[now.to][now.st]^k.wgt)) continue;
						dis[k.to][0]=(dis[now.to][now.st]^k.wgt);
						qq.push(ei{k.to,dis[k.to][0],0});
					}
				}
			}	
			if (dis[b][1]!=inf) printf("1\n");
			else printf("0\n");
	}	
	return 0;
}
