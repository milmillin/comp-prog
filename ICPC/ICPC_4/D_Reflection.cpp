#include <cstdio>
#include <cmath>

using namespace std;

struct vec {
	double x,y,z;
	double len() const {
		return sqrt(x*x+y*y+z*z);
	}
	vec scale(double ss) const {
		return vec{ss*x,ss*y,ss*z};
	}
	vec normalized() {
		return this->scale(1.0/this->len());
	}
};

vec operator- (const vec &a, const vec &b) {
	return vec{a.x-b.x,a.y-b.y,a.z-b.z};
}

vec operator+ (const vec &a, const vec &b) {
	return vec{a.x+b.x,a.y+b.y,a.z+b.z};
}

double operator* (const vec &a, const vec &b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

int main () {
	double x,y,z;
	scanf("%lf%lf%lf",&x,&y,&z);
	int cmd;
	scanf("%d",&cmd);
	double a,b,c,d,e,f;
	
	vec pnt1 = vec{x,y,z};	

	if (cmd==1) {
		scanf("%lf%lf%lf",&a,&b,&c);
		vec pnt2 = vec{a,b,c};
		
		vec ans = (pnt2-pnt1).scale(2)+pnt1;
		
		printf("%f %f %f\n",ans.x,ans.y,ans.z);

	} else if (cmd==2) {
		scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
		vec aa = vec{a,b,c};
		vec nn = (vec{d,e,f}-aa).normalized();
		
		vec ans = ((aa-pnt1)-nn.scale((aa-pnt1)*nn)).scale(2)+pnt1;
		printf("%f %f %f\n",ans.x,ans.y,ans.z);
	} else {
		scanf("%lf%lf%lf%lf",&a,&b,&c,&d);

		vec vv = vec{a,b,c};
		vec xx;
		if (a!=0) {
			xx = vec{d/a,0,0};
		} else if (b!=0) {
			xx = vec{0,d/b,0};
		} else {
			xx = vec{0,0,d/c};
		}
		vec ww = xx-pnt1;
		//printf("%f %f %f\n",ww.x,ww.y,ww.z);
		//printf("%f\n",vv*ww);	
		vec ans = vv.normalized().scale((vv*ww)*2)+pnt1;
		printf("%f %f %f\n",ans.x,ans.y,ans.z);
	}
	return 0;
}
