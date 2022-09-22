#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int r,g,b;

double h[100][100];
double s[100][100];
double l[100][100];

double hA,sA,lA;
int hC,sC,lC;

int main () {
	int w,h;
	scanf("%d%d",&w,&h);
	for (int i=0;i<w;i++) {
		for (int j=0;j<h;j++) {
			scanf("%d%d%d",&r,&g,&b);
			double mn = min(r,min(g,b))/255.0;
			double mx = max(r,max(g,b))/255.0;
			double _l=(mx+mn)/2.0;
			lA+=_l;
			lC++;
			if (mx==mn) continue;

			double _s;
			if (_l<0.5) {
				_s=(double)(mx-mn)/(mx+mn);
			} else {
				_s=(double)(mx-mn)/(2.0-mx-mn);
			}
			sA+=_s;
			sC++;

			double _h;
			if (mx*255-r<1e-6) {
				_h=(double)(g-b)/(mx-mn)/255.0;
			} else if (mx*255-g<1e-6) {
				_h=2.0+(double)(b-r)/(mx-mn)/255.0;
			} else if (mx*255-b<1e-6) {
				_h=4.0+(double)(r-g)/(mx-mn)/255.0;
			}

			_h*=60;
			_h=fmod(_h,360);
			_h+=360;
			_h=fmod(_h,360);
			
			hA+=_h;
			hC++;
		}
	}
	hA/=hC;
	sA/=sC;
	lA/=lC;
	/*
	printf("%f %f %f\n",hA,sA,lA);
	printf("%d %d %d\n",hC,sC,lC);
	*/
	if (sA<0.5) {
		if (lA<0.4) {
			printf("M\n");
		} else {
			printf("A\n");
		}
	} else {
		printf("3\n");
	}
	return 0;
}
