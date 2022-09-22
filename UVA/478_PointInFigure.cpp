#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct r {
	int i;
	double xmin,ymax,xmax,ymin;
};

struct cc{
	int i;
	double x,y,r;
};

struct t{
	int i;
	double x1,y1,x2,y2,x3,y3;
};

vector<r> rect;
vector<cc> cir;
vector<t> tri;

double addAng(double x1,double y1, double x2, double y2, double x3, double y3) {
	
	double a=(x3-x1)*(y2-y1)-(x2-x1)*(y3-y1);
	double ang = acos(((x3-x1)*(x2-x1)+(y3-y1)*(y2-y1))/sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
	if (abs(abs(ang)-6.283185307)<1e-6) return 215.25;
	if (a<0) return -ang;
	if (a==0) return 0;
	return ang;	
}

bool in(double x, double y, t &aa) {
	double cnt=0;
	double a;
	cnt+=addAng(x,y,aa.x1,aa.y1,aa.x2,aa.y2);
	cnt+=addAng(x,y,aa.x2,aa.y2,aa.x3,aa.y3);
	cnt+=addAng(x,y,aa.x3,aa.y3,aa.x1,aa.y1);
	//printf("%f %f %f\n",x,y,cnt);
	if (abs(abs(cnt)-6.283185307)<1e-6) return true;
	return false;
}

int main () {
	char xx;
	double a,b,c,d,e,f;
	int cnt=1;
	while (true) {
		//printf("%d\n",cnt);
		scanf(" %c",&xx);
		if (xx=='r') {
			//rectangle
			scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
			rect.push_back(r{cnt,a,b,c,d});
		} else if (xx=='c') {
			//circle
			scanf("%lf%lf%lf",&a,&b,&c);
			cir.push_back(cc{cnt,a,b,c});
		} else if (xx=='t') {
			//triangle
			scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
			tri.push_back(t{cnt,a,b,c,d,e,f});
		} else if (xx=='*') break;
		cnt++;
	}
	double x,y;
	cnt=1;
	while (true) {
		scanf("%lf%lf",&x,&y);
		if (x==9999.9&&y==9999.9) break;
		vector<int> ans;
		for (int i=0;i<rect.size();i++) {
			if (x>rect[i].xmin&&x<rect[i].xmax&&y>rect[i].ymin&&y<rect[i].ymax) ans.push_back(rect[i].i);
		}
		for (int i=0;i<cir.size();i++) {
			if ((x-cir[i].x)*(x-cir[i].x)+(y-cir[i].y)*(y-cir[i].y)<cir[i].r*cir[i].r) ans.push_back(cir[i].i);
		}
		for (int i=0;i<tri.size();i++) {
			if (in(x,y,tri[i])) ans.push_back(tri[i].i);
		}
		sort(ans.begin(),ans.end());
		if (ans.size()==0) {
			printf("Point %d is not contained in any figure\n",cnt);
		}
		for (int i=0;i<ans.size();i++) {
			printf("Point %d is contained in figure %d\n",cnt,ans[i]);
		}
		cnt++;
	}
	return 0;	
}
