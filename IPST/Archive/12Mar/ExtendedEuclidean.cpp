#include <cstdio>

using namespace std;

int gcd (int a, int b) {
	if (a%b==0) return b;
	return gcd(b,a%b);
}

int ext (int a, int b, int &x, int &y) {
	if (a%b==0) {
		x=0;
		y=1;
		return b;
	}
	int x1,y1;
	int g=ext(b,a%b,x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
	return g;
}

int main () {
	int x,y;
	printf("%d\n",ext(2367,3016,x,y));
	printf("%d %d\n",x,y);
	return 0;
}
