#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct point {
	int id;
	double x,y;
};

struct edge {
	int a,b;
	long long wgt;
};

bool cmp2 (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

bool operator< (const point &a, const point &b) {
	if (a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

long long dis(const point &a, const point &b) {
	return (a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x);
}

vector<point> line[20];
double slope[20];
double yint[20];
bool isVer[20];
vector<edge> ee;
int par[50100];

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}

void jn(int a,int b) {
	par[findPar(a)]=findPar(b);
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int s,x,y;
	int cur=0;
	for (int i=0;i<m;i++) {
		scanf("%d",&s);
		for (int j=0;j<s;j++) {
			scanf("%d%d",&x,&y);
			line[i].push_back(point{cur,(double)x,(double)y});
			if (j) ee.push_back(edge{cur-1,cur,dis(line[i][j],line[i][j-1])});
			cur++;
		}
		sort(line[i].begin(),line[i].end());
		slope[i]=(double)(line[i][1].y-line[i][0].y)/(line[i][1].x-line[i][0].x);
		if (line[i][1].x==line[i][0].x) {
			isVer[i]=true;
			yint[i]=line[i][0].x;
		} else {
			yint[i]=line[i][0].y-slope[i]*line[i][0].x;
		}
	}
	//printf("YAY\n");
	for (int i=0;i<m;i++) {
		for (int j=0;j<(int)line[i].size();j++) {
			//for each point
			for (int k=0;k<m;k++) {
				//for each line;
				if (k==i) continue;
				double ss=-1.0/slope[k];
				double cc=line[i][j].y-ss*line[i][j].x;
				double intx,inty;
				if (isVer[k]) {
					intx=yint[k];
					inty=line[i][j].y;
				} else if (slope[k]==0) {
					intx=line[i][j].x;
					inty=yint[k];
				} else {
					intx=(cc-yint[k])/(slope[k]-ss);
					inty=ss*intx+cc;
				}
				vector<point>::iterator pnt=upper_bound(line[k].begin(),line[k].end(),point{-1,intx,inty});
				//ee.push_back(edge{pnt->id,(pnt+1)->id,dis(*pnt,*(pnt+1))});
				//printf("%d\n",pnt->id);
				if(pnt!=line[k].end()) ee.push_back(edge{line[i][j].id,pnt->id,dis(line[i][j],*pnt)});
				if (pnt!=line[k].begin()) {
					pnt--;
					//printf("%d\n",pnt->id);
					ee.push_back(edge{line[i][j].id,pnt->id,dis(line[i][j],*pnt)});
				}
			}
		}
	}
	sort(ee.begin(),ee.end(),cmp2);
	for (int i=0;i<cur;i++) {
		par[i]=i;
	}
	long long ans=0;
	for (int i=0;i<(int)ee.size();i++) {
		//printf("%d %d %I64d\n",ee[i].a,ee[i].b,ee[i].wgt);
		if (findPar(ee[i].a)==findPar(ee[i].b)) continue;
		jn(ee[i].a,ee[i].b);
		ans+=ee[i].wgt;
	}
	printf("%I64d\n",ans);
	return 0;
}
