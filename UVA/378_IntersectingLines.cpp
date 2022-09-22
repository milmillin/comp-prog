#include <cstdio>

using namespace std;

double m(int x1,int y1,int x2,int y2) {
	return (double)(y2-y1)/(x2-x1);
}

double c(double m, double x1, double y1) {
	return y1-m*x1;
}

int main () {
	int n;
	scanf("%d",&n);
	printf("INTERSECTING LINES OUTPUT\n");
	int x1,y1,x2,y2,x3,y3,x4,y4;
	while (n--) {
		scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
		double m1 = m(x1,y1,x2,y2);
		double m2 = m(x3,y3,x4,y4);
		double c1 = c(m1,x1,y1);
		double c2 = c(m2,x3,y3);
		if (x1!=x2&&x3!=x4) {
			if (m1==m2) {
				if (c1==c2) {
					printf("LINE\n");
				} else {
					printf("NONE\n");
				}
			} else {
				printf("POINT %.2f %.2f\n",(c2-c1)/(m1-m2),m1*(c2-c1)/(m1-m2)+c1);
			}
		} else if (x1==x2&&x3==x4) {
			if (x1==x3) {
				printf("LINE\n");
			} else {
				printf("NONE\n");
			}
		} else if (x1==x2) {
			printf("POINT %.2f %.2f\n",(double)x1,m2*x1+c2);
		} else if (x3==x4) {
			printf("POINT %.2f %.2f\n",(double)x3,m1*x3+c1);
		}
	}
	printf("END OF OUTPUT\n");
	return 0;
}
