#include <cstdio>
#include <vector>
#include <map>
#include <cfloat>
#include <cmath>

using namespace std;

struct vec{
	double x,y;
	vec operator+(vec &a) {
		return vec{x+a.x,y+a.y};
	}	
	vec operator-(vec &a) {
		return vec{x-a.x,y-a.y};
	}
	vec operator*(double k) {
		return vec{x*k,y*k};
	}
	double operator*(vec &a) {
		return x*a.x+y*a.y;
	}
};

struct line{
	double a,b,c;
};

double eps=DBL_EPSILON;

bool operator<(const line &a, const line &b) {
	if (abs(a.a-b.a)>eps) return a.a-b.a>eps;
	if (abs(a.b-b.b)>eps) return a.b-b.b>eps;
	return a.c-b.c>eps;
}



vector<vec> pnt;
map<line,int> mp;

int main () {
	int n;
	scanf("%d",&n);
	double a,b;
	for (int i=0;i<n;i++) {
		scanf("%lf%lf",&a,&b);
		pnt.push_back(vec{a,b});
	}
	for (int i=0;i<n;i++) {
		for (int j=i+1;j<n;j++) {
			double a=(pnt[i].y-pnt[j].y);
			double b=(pnt[j].x-pnt[i].x);
			double c=(pnt[i].x*pnt[j].y-pnt[j].x*pnt[i].y);
			vec mid = (pnt[i]-pnt[j])*0.5+pnt[j];
			line ll = line{a,b,c};
			if (abs(ll.a-0)<eps) {
				double xx=ll.b;
				ll.a/=xx;
				ll.b/=xx;
				ll.c/=xx;
			} else {
				//printf("%f %f %f\n",ll.a,ll.b,ll.c);
				double xx=ll.a;
				ll.a/=xx;
				ll.b/=xx;
				ll.c/=xx;
			}
			vec pp = vec{b,-a};
			double res=pp*mid;
			line ppp = line{b,-a,-res};
			if (abs(ppp.a-0)<eps) {
				double xx=ppp.b;
				ppp.a/=xx;
				ppp.b/=xx;
				ppp.c/=xx;
			} else {
				double xx=ppp.a;
				ppp.a/=xx;
				ppp.b/=xx;
				ppp.c/=xx;
			}			
			//printf("%d %d\n%.2f %.2f %.2f\n%.2f %.2f %.2f\n",i,j,ppp.a,ppp.b,ppp.c,ll.a,ll.b,ll.c);
			mp[ll]++;
			mp[ppp]++;
		}
	}
	//printf("* %d\n",mp.size());
	int cnt=0;
	for (auto it:mp) {
		//printf("%.2f %.2f %.2f %d\n",it.first.a,it.first.b,it.first.c,it.second);
		if (it.second==n/2) cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}
