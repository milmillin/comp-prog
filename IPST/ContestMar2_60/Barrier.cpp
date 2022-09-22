#include <cstdio>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

struct point {
	double x,y;
	double aa;
	double dd;
	point operator-(const point &r) const {
		return point{x-r.x,y-r.y};
	}
	void print() const {
		printf("%f %f %f\n",x,y,aa);
	}
};

point p0;
double pi=atan(1)*4;
double eps=1e-7;

double ang(const point &r) {
	double res = atan((r.y-p0.y)/(r.x-p0.x));	
	if (r.x<p0.x) res+=pi;
	return res;
}


double dis(const point &a, const point &b) {
	point c=a-b;
	return sqrt(c.x*c.x+c.y*c.y);			
}

double orient(const point &a, const point &b, const point &c) {
	point p1=b-a;
	point p2=c-a;
	//printf("yy\n");
	//p1.print();
	//p2.print();
	return p1.x*p2.y-p2.x*p1.y;
	// left positive
}


bool operator< (const point &a, const point &b) {
	//double o = orient(p0,a,b);
	//if (o!=0) return o>0;
	if (a.aa!=b.aa) //return a.aa<b.aa;
		return a.aa-b.aa<eps;
	return a.dd<b.dd;
}

set<point> pts;

set<point>::iterator left(set<point>::iterator x, set<point> &s) {
	if (x==s.begin()) {
		x=s.end();
		x--;
		return x;
	}
	x--;
	return x;
}

set<point>::iterator right(set<point>::iterator x, set<point> &s) {
	x++;
	if (x==s.end()) x=s.begin();
	return x;
}


int main () {
	int n;
	double curdis=0;
	scanf("%d",&n);

	double a,b;
	scanf("%lf%lf",&a,&b);
	point p1 = point{a,b};
	
	printf("%f\n",curdis);

	scanf("%lf%lf",&a,&b);
	point p2=point{a,b};
	
	curdis=2*dis(p1,p2);
	printf("%f\n",curdis);

	scanf("%lf%lf",&a,&b);
	point p3=point{a,b};

	curdis=dis(p1,p2)+dis(p2,p3)+dis(p3,p1);
	printf("%f\n",curdis);
	
	p0=point{(p1.x+p2.x+p3.x)/3,(p1.y+p2.y+p3.y)/3};
	
	p1.aa=ang(p1);
	p1.dd=dis(p0,p1);
	p2.aa=ang(p2);
	p2.dd=dis(p0,p2);	
	p3.aa=ang(p3);
	p3.dd=dis(p0,p3);

	pts.insert(p1);
	pts.insert(p2);
	pts.insert(p3);

	set<point>::iterator aa;
	set<point>::iterator bb;
	for (int i=3;i<n;i++) {
		scanf("%lf%lf",&a,&b);
		point tmp=point{a,b};
		tmp.aa=ang(tmp);
		tmp.dd=dis(p0,tmp);

		//if (tmp.x==p0.x&&tmp.y==p0.y) {
			//printf("%f\n",curdis);
			//continue;
		//}

		auto cur = pts.insert(tmp).first;
		auto prev = left(cur,pts);
		auto next = right(cur,pts);
		
		//for (auto &i:pts) {
			//i.print();
		//}
		//printf("--\n");

		if (orient(*prev,*cur,*next)<eps) {
			//is not in convex hull
			pts.erase(tmp);
			printf("%f\n",curdis);
			continue;
		}
		curdis-=dis(*prev,*next);
		curdis+=dis(*prev,*cur);
		curdis+=dis(*cur,*next);

		while (pts.size()>3) {
			aa=left(cur,pts);
			bb=left(aa,pts);	
			if (orient(*bb,*aa,*cur)>0) break;
			//remove aa
			curdis-=dis(*bb,*aa);
			curdis-=dis(*aa,*cur);
			curdis+=dis(*bb,*cur);
			pts.erase(aa);
		}
		while (pts.size()>3) {
			aa=right(cur,pts);
			bb=right(aa,pts);
			if (orient(*cur,*aa,*bb)>0) break;
			//remove aa;
			curdis-=dis(*bb,*aa);
			curdis-=dis(*aa,*cur);
			curdis+=dis(*bb,*cur);
			pts.erase(aa);
		}
		printf("%f\n",curdis);
	}
	
	return 0;
}
