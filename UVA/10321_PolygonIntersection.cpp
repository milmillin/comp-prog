#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class point{
	public:
	double x,y;
	point();
	point(double a,double b);
	point operator+(const point &a);
	point operator-(const point &a);
	point scale(double c);
	double cross(const point &a);
};

point::point() {
	x=0;
	y=0;
}

point::point(double a,double b) {
	x=a;
	y=b;
}

point point::operator+ (const point &a) {
	return point(x+a.x,y+a.y);
}

point point::operator- (const point &a) {
	return point(x-a.x,y-a.y);
}

point point::scale(double c) {
	return point(c*x,c*y);
}

double point::cross(const point &a) {
	//printf("%.2f %.2f %.2f %.2f\n",x,a.y,a.x,y);
	return x*a.y-a.x*y;
}

point isect(point &a,point &b,point &c,point &d) {
	//printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",a.x,a.y,b.x,b.y,c.x,c.y,d.x,d.y);
	double chk = (b-a).cross(c-a)*(b-a).cross(d-a);
	double chk2 = (d-c).cross(a-c)*(d-c).cross(b-c);
	if (chk2>0||chk>0) return point(-200,-200);
	double s=-((d-c).cross(a-c)/(d-c).cross(b-a));
	//printf("%f\n",s);
	if (s>1||s<0) return point(-200,-200);
	return a+(b-a).scale(s);
}

bool cmp(const point &a, const point &b) {
	if (a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}

int main () {
	int n1,n2;
	while (true) {
		scanf("%d",&n1);
		if (n1<3) break;
		vector<point> p1(n1);
		for (int i=0;i<n1;i++) {
			scanf("%lf%lf",&p1[i].x,&p1[i].y);
		}
		
		scanf("%d",&n2);
		vector<point> p2(n2);
		for (int i=0;i<n2;i++) {
			scanf("%lf%lf",&p2[i].x,&p2[i].y);
		}
		
		vector<point> inter;
		point tmp;
		for (int i=0;i<n1;i++) {
			for (int j=0;j<n2;j++) {
				tmp=isect(p1[i],p1[(i+1)%n1],p2[j],p2[(j+1)%n2]);
				if (tmp.x==-200&&tmp.y==-200) continue;
				//printf("%d %d\n",i,j);
			//	printf("--%.2f %.2f\n",tmp.x,tmp.y);
				inter.push_back(tmp);
			}
		}
		sort(inter.begin(),inter.end(),cmp);
		printf("%d\n",inter.size());
		for (int i=0;i<inter.size();i++) {
			printf("%.2f %.2f\n",inter[i].x,inter[i].y);
		}
	}
	return 0;
}
