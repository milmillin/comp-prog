#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps = 1e-9;

bool GE(double a, double b) {
	return (a-b>eps)||(abs(a-b)<eps);
}

bool LE(double a, double b) {
	return (b-a>eps)||(abs(a-b)<eps);
}

bool isBet(double a,int x, int y) {
	if (y<x) swap(x,y);
	if (GE(a,x)&&LE(a,y)) return true;
	return false;
}

double mapXY(double val, int x1,int y1,int x2,int y2) {
	if (x2==x1) return -1;
	return (val-x1)/(x2-x1)*(y2-y1)+y1;
}

double mapYX(double val, int x1,int y1,int x2,int y2) {
	if (y2==y1) return -1;
	return (val-y1)/(y2-y1)*(x2-x1)+x1;
}

int main () {
	int n;
	scanf("%d",&n);
	int x1,y1,x2,y2,a1,b1,a2,b2;
	bool ans;
	while (n--) {
		scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&a1,&b1,&a2,&b2);
		ans=false;
		if ((isBet(x1,a1,a2)&&isBet(y1,b1,b2))||(isBet(x2,a1,a2)&&isBet(y2,b1,b2))) ans=true;
		if (isBet(b1,y1,y2)) {
			//printf("1\n");
			//printf("%f\n",mapYX(b1,x1,y1,x2,y2));
			if (y1==y2) {
				ans=ans||(isBet(x1,a1,a2)||isBet(x2,a1,a2));
			} else {
				ans=ans||isBet(mapYX(b1,x1,y1,x2,y2),a1,a2);
			}
		}
		if (isBet(b2,y1,y2)) {
			//printf("2");
			if (y1==y2) {
				ans=ans||(isBet(x1,a1,a2)||isBet(x2,a1,a2));
			} else {
				ans=ans||isBet(mapYX(b2,x1,y1,x2,y2),a1,a2);
			}
		}
		if (isBet(a1,x1,x2)) {
			//printf("3");
			if (x1==x2) {
				ans=ans||(isBet(y1,b1,b2)||isBet(y2,b1,b2));
			} else {
				ans=ans||isBet(mapXY(a1,x1,y1,x2,y2),b1,b2);
			}
		}
		if (isBet(a2,x1,x2)) {
			//printf("4");
			if (x1==x2) {
				ans=ans||(isBet(y1,b1,b2)||isBet(y2,b1,b2));
			} else {
				ans=ans||isBet(mapXY(a2,x1,y1,x2,y2),b1,b2);
			}
		}
		printf("%c\n",(ans)?'T':'F');
	}
	return 0;
}
