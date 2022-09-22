#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct point {
	double x,y;
};

double addAng(double x1,double y1, double x2, double y2, double x3, double y3) {
	
	double a=(x3-x1)*(y2-y1)-(x2-x1)*(y3-y1);
	double ang = acos(((x3-x1)*(x2-x1)+(y3-y1)*(y2-y1))/sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
	if (a<0) return -ang;
	if (a==0) return 0;
	return ang;	
}

int main () {
	while (true) {
		int n;
		scanf("%d",&n);
		if (n==0) break;
		vector<point> tbl(n);
		for (int i=0;i<n;i++) {
			scanf("%lf%lf",&tbl[i].x,&tbl[i].y);
		}
		point p;
		scanf("%lf %lf",&p.x,&p.y);
		double ang=0;
		for (int i=0;i<n;i++) {
			ang+=addAng(p.x,p.y,tbl[i].x,tbl[i].y,tbl[(i+1)%n].x,tbl[(i+1)%n].y);
		}
		if (abs(abs(ang)-6.283185307)<1e-6) {
			printf("T\n");
		} else {
			printf("F\n");
		}
	}
	return 0;
}
