#include <cstdio>
#include <cmath>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	int p,x,y;
	double PI = 3.14159265358979323846;
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d",&p,&x,&y);
		double ang = atan((double)(x-50)/(y-50));
		double dis = sqrt((x-50)*(x-50)+(y-50)*(y-50));
		if (y-50<0) {
			ang=PI-ang;			
		} else {
			//ang = atan((double)(x-50)/(y-50));
			if (signbit(ang)) ang=2*PI+ang;
		}
		//if (signbit(ang)) {
		//	ang+=2*3.14159265358979323846;
		//}
		printf("Case #%d: %s\n",i,(ang*50/PI<=p&&dis<=50)?"black":"white");
	}
	return 0;
}
