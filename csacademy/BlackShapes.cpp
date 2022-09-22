#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

bool isBlack[1010][1010];

struct cell {
	int r,c;
};

queue<cell> q;
bool visit[1010][1010];
int num[1010][1010];
int sz[1000100];
int cur=0;

int di[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	int x;
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			scanf("%d",&x);
			if (x) isBlack[i][j]=true;
		}
	}
	int nowr,nowc;
	int nextr,nextc;
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			if (visit[i][j]) continue;
			if (!isBlack[i][j]) continue;
			cur++;
			visit[i][j]=true;
			q.push(cell{i,j});
			while (!q.empty()) {
				nowr=q.front().r;
				nowc=q.front().c;
				q.pop();
				num[nowr][nowc]=cur;
				sz[cur]++;
				for (int k=0;k<4;k++) {
					nextr=nowr+di[k][0];
					nextc=nowc+di[k][1];
					if (nextr<0||nextc<0||nextr>=r||nextc>=c) continue;
					if (!isBlack[nextr][nextc]) continue;
					if (visit[nextr][nextc]) continue;
					visit[nextr][nextc]=true;
					q.push(cell{nextr,nextc});
				}
			}
		}
	}
	//for (int i=0;i<r;i++) {
		//for (int j=0;j<c;j++) {
			//printf("%d ",num[i][j]);
		//}
		//printf("\n");
	//}
	int mx=0;
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			if (isBlack[i][j]) continue;
			//printf("%d %d\n",i,j);
			int now=1;
			for (int k=0;k<4;k++) {
				bool add=true;
				if (i+di[k][0]<0||i+di[k][0]>=r||j+di[k][1]<0||j+di[k][1]>=c) continue;
				//printf("%d %d %d\n",i+di[k][0],j+di[k][1],num[i+di[k][0]][j+di[k][1]]);
				for (int l=0;l<k;l++) {
					//printf("%d\n",l);
					if (i+di[l][0]<0||i+di[l][0]>=r||j+di[l][1]<0||j+di[l][1]>=c) continue;
					//printf("-%d %d %d\n",i+di[l][0],j+di[l][1],num[i+di[l][0]][j+di[l][1]]);
					if (num[i+di[k][0]][j+di[k][1]]==num[i+di[l][0]][j+di[l][1]]) {
						add=false;
						break;
					}
				}
				if (add) now+=sz[num[i+di[k][0]][j+di[k][1]]]; 
			}
			//printf("%d ",now);
			mx=max(mx,now);
		}
		//printf("\n");
	}
	printf("%d\n",mx);
	return 0;
}
