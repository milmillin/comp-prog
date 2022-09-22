#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	int id,x,y;
};

struct edge {
	int from,to;
	long long wgt;
};

bool cmp (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

long long dis(point &a, point &b) {
	return (long long)(a.x-b.x)*(a.x-b.x)+(long long)(a.y-b.y)*(a.y-b.y);
}

vector<point> pnt[320][320];
vector<point> tbl;
vector<edge> ee;

int di[5][2]={{0,0},{0,1},{1,-1},{1,0},{1,1}};

int par[100100];

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}

void jn(int i,int j) {
	par[findPar(i)]=findPar(j);
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		par[i]=i;
	}
	int minx=2e9,miny=2e9,maxx=-2e9,maxy=-2e9;
	int x,y;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		tbl.push_back(point{i,x,y});
		minx=min(minx,x);
		miny=min(miny,y);
		maxx=max(maxx,x);
		maxy=max(maxy,y);
	}
	double blkX=1010;
	double blkY=1010;
	int mxx=maxx/blkX+1;
	int mxy=maxy/blkY+1;
	//printf("%f %f %d\n",blkX,blkY,sz);
	for (int i=0;i<n;i++) {
		//printf("%d %d\n",(int)((tbl[i].x+minx)/blkX),(int)((tbl[i].y+miny)/blkY));
		pnt[(int)((tbl[i].x-minx)/blkX)][(int)((tbl[i].y-miny)/blkY)].push_back(tbl[i]);
	}
	//printf("yay\n");
	int nx,ny;
	long long tmp;
	for (int i=0;i<=mxx;i++) {
		for (int j=0;j<=mxy;j++) {
			for (int k=0;k<(int)pnt[i][j].size();k++) {
				for (int l=0;l<5;l++) {
					nx=i+di[l][0];
					ny=j+di[l][1];
					if (nx<0||ny<0||nx>mxx||ny>mxy) continue;
					int st=0;
					if (nx==i&&ny==j) st=k+1;
					//printf("%d %d %d %d\n",i,j,nx,ny);
					for (int m=st;m<(int)pnt[nx][ny].size();m++) {
						//if (pnt[i][j][k].id==pnt[nx][ny][m].id) continue;
						tmp=dis(pnt[i][j][k],pnt[nx][ny][m]);
						if (tmp>1030000) continue;
						ee.push_back(edge{pnt[i][j][k].id,pnt[nx][ny][m].id,tmp});
					}
				}
			}

		}
	}
	sort(ee.begin(),ee.end(),cmp);
	long long ans=0;
	for (int i=0;i<(int)ee.size();i++) {
		if (findPar(ee[i].from)==findPar(ee[i].to)) continue;
		jn(ee[i].from,ee[i].to);
		ans+=ee[i].wgt;
	}
	printf("%I64d\n",ans);
	return 0;
}
