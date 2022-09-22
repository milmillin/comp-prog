#include <cstdio>

using namespace std;

int main () {
	int a=5;
	int b=7;

	int* tmp = &a;
	&a=&b;
	&b=tmp;

	return 0;
}
