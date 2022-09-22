#include <cstdio>
#include <cmath>

using namespace std;

double PI = 3.14159265358979323846264338;

int main () {

	double a,b,z;
	scanf("%lf%lf%lf",&a,&b,&z);
	if (180-a-b<0.000001) {
		printf("%f\n",z*cos((90-b)*PI/180)*PI/2);
		return 0;
	}
	double a1,b1,c1,a2,b2,c2;
	double x1,y1,x2,y2,x3,y3,x4,y4;
	x1 = 0;
	y1=0;
	x3=z;
	y3=0;
	x2 = cos((a-90)*PI/180.0);
	y2 = sin((a-90)*PI/180.0);
	x4 = cos((90-b)*PI/180.0)+z;
	y4 = sin((90-b)*PI/180.0);
	
	a1=y1-y2;
	b1=x2-x1;
	c1=x1*y2-x2*y1;

	a2=y3-y4;
	b2=x4-x3;
	c2=x3*y4-x4*y3;

	double x,y;
	x=(c1*b2-b1*c2)/(b1*a2-a1*b2);
	y=(a1*c2-c1*a2)/(b1*a2-a1*b2);

	double r = sqrt(x*x+y*y);

	printf("%f\n",(a+b)*PI*r/180.0);
	
	return 0;
}
