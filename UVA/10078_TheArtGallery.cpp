#include <cstdio>
#include <vector>

using namespace std;

class point{
	public:
	int x,y;
	point();
	point(int a,int b);
	point operator+(const point &a);
	point operator-(const point &a);
};

point::point() {
	x=0;
	y=0;
}

point::point(int a,int b) {
	x=a;
	y=b;
}

point point::operator+(const point &a) {
	return point(x+a.x,y+a.y);
}

point point::operator-(const point &a) {
	return point(x-a.x,y-a.y);
}

double cross(const point &a, const point &b) {
	//printf("%d %d %d %d\n",a.x,b.y,b.x,a.y);
	return a.x*b.y-b.x*a.y;
}

int main () {
	while (true) {
		int n;
		scanf("%d",&n);
		if (n==0) break;
		vector<point>p(n);
		double left;
		double last;
		bool ans=false;
		for (int i=0;i<n+2;i++) {
			if (i<n) scanf("%d%d",&p[i].x,&p[i].y);
			if (i>=2) {
				left = cross(p[i%n]-p[(i-2)%n],p[(i-1)%n]-p[(i-2)%n]);
				//printf("%f\n",left);
				if (i>2) {
					if (left*last<0) ans=true;
				}
				last=left;
			}
		}
		printf("%s\n",(ans)?"Yes":"No");
	}
	return 0;
}
