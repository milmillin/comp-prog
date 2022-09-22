#include <cstdio>
#include <iostream>

using namespace std;
double sq(double k)
{
	return k*k;
}
int main () {
	double x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	double a = x1*(y2-y3) - y1*(x2-x3) + x2*y3-x3*y2;
	double b = (sq(x1) + sq(y1))*(y3-y2) + (sq(x2)+sq(y2))*(y1-y3) + (sq(x3)+sq(y3))*(y2-y1);
	double c = (sq(x1) + sq(y1))*(x2-x3) + (sq(x2)+sq(y2))*(x3-x1) + (sq(x3)+sq(y3))*(x1-x2);
	double x = -b/2/a;
	double y = -c/2/a;
	printf("%f %f\n", x, y);	
}
