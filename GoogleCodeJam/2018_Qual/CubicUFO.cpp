#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

// - x-axis
// | y-axis
// / z-axis

struct point {
	double x,y,z;
	point operator+ (const point &r) const {
		return point{x+r.x,y+r.y,z+r.z};
	}	
	point operator- (const point &r) const {
		return point {x-r.x,y-r.y,z-r.z};
	}
	point rotateZ (double a) const {
		return point {x*cos(a)-y*sin(a),x*sin(a)+y*cos(a),z};		
	}
	point rotateX (double a) const {
		return point {x,y*cos(a)-z*sin(a),y*sin(a)+z*cos(a)};
	}	
	void print() const {
		printf("%f %f %f\n",x,y,z);
	}
};

const double sq2=sqrt(2);
const double pi4=atan(1);
const double eps=1e-9;

void f() {
	double a;
	scanf("%lf",&a);
	point p1=point{0.5,0,0};
	point p2=point{0,0.5,0};
	point p3=point{0,0,0.5};
	double hi=pi4;
	double lo=0;
	double mid;
	if (a<=sq2) {
		while (hi-lo>eps) {
			mid=(hi+lo)/2;
			if (cos(mid)+sin(mid)<a) lo=mid;
			else hi=mid;			
		}
		//printf("%f %f %f\n",lo,cos(lo)+sin(lo),pi4);
		p1.rotateX(lo).print();
		p2.rotateX(lo).print();
		p3.rotateX(lo).print();
	} else {
		while (hi-lo>eps) {
			mid=(hi+lo)/2;
			if (sin(mid)+sq2*cos(mid)<a) lo=mid;
			else hi=mid;
		}
		p1.rotateX(pi4).rotateZ(lo).print();
		p2.rotateX(pi4).rotateZ(lo).print();
		p3.rotateX(pi4).rotateZ(lo).print();
	}	
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d:\n",i);
		f();
	}
	return 0;
}
