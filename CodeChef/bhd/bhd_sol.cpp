#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

const double PI=acos(-1); 
int N;

struct torus{
	double x,y,z,R,r;
}A[22];

double r0[22];

struct event{
	double x;int v;
	bool operator<(const event&e)const{return x<e.x;}
}E[222];

int tot;

// current circle is at (0, 0), R
// other circle is at (x, y), r
void ins(double x,double y,double R,double r,int v){

	double d=sqrt(x*x+y*y);

	// return if circles are disjoint
	// of if other circle is in current circle
	if(d>=R+r||d<=R-r)return;

	// if current circle is in other circle
	// add range [0, 2*PI]
	if(d<=r-R){
		E[tot++]=(event){0,v};
		E[tot++]=(event){2*PI,-v};
		return;
	}

	double a=atan2(y,x);
	double b=acos((R*R + d*d - r*r) / (2*R*d));

	// xl and xr: range of angle that other circle
	// intersect with current circle
	double xl=a-b;
	double xr=a+b;

	while (xl<0) {
		xl+=2*PI;
		xr+=2*PI;
	}

	// add range [xl, xr]
	E[tot++]=(event){xl,v};

	if (xr<=2*PI) {
		E[tot++]=(event){xr,-v};
	} else {
		E[tot++]=(event){2*PI,-v};
		E[tot++]=(event){0,v};
		E[tot++]=(event){xr-2*PI,-v};
	}
}

double cover(double x,double y,double r,int i){
	tot=0;
	// consider other ring
	for (int j=0;j<N;j++) {
		if (j!=i&&r0[j]>0) {
			ins(A[j].x-x,A[j].y-y,r,A[j].R+r0[j],1);
			ins(A[j].x-x,A[j].y-y,r,A[j].R-r0[j],-1);
		}
	}

	// sweep angle
	std::sort(E,E+tot);

	int v=0;
	double la=0;
	double s=0;

	E[tot].x=2*PI;

	//
	for (int i=0;i<=tot;i++){
		if (!v) {
			s += r*r * (E[i].x-la); // r^2 * angle
			s += (x+r*cos(la))*y;
			s -= x*(y+r*sin(la));
			s += x*(y+r*sin(E[i].x));
			s -= (x+r*cos(E[i].x))*y;
		}
		la=E[i].x;v+=E[i].v;
	}
	//puts("");
	return s/2;
}

// calculate area of union of rings at given z
double f(double z){
	// calculate radii of ring at given z as r0, an offset from R 
	for(int i=0;i<N;i++){
		r0[i]=A[i].r*A[i].r-(A[i].z-z)*(A[i].z-z);
		r0[i]=r0[i]>0?sqrt(r0[i]):0;
	}
	// sum the area
	double sum=0;
	for(int i=0;i<N;i++)if(r0[i]>0)
		// cover(bigger circle) - cover(smaller circle)
		sum+=cover(A[i].x,A[i].y,A[i].R+r0[i],i)-cover(A[i].x,A[i].y,A[i].R-r0[i],i);
	return sum;
}

// simpson's rule of numerical integration
double calc(double l,double r,double fl,double fm,double fr){
	double m=(l+r)/2,f1=f((l+m)/2),f2=f((m+r)/2),s=(fl+fm*4+fr)/6*(r-l),
		s1=(fl+f1*4+fm)/6*(m-l),s2=(fm+f2*4+fr)/6*(r-m);
	if(r-l<0.1&&fabs(s-s1-s2)<1e-9)return s1+s2;
	return calc(l,m,fl,f1,fm)+calc(m,r,fm,f2,fr);
}

int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lf%lf%lf%lf%lf",&A[i].x,&A[i].y,&A[i].z,&A[i].R,&A[i].r),A[i].x+=1e-9*i;
	printf("%lf\n",calc(-1000,1000,f(-1000),f(0),f(1000)));
}
