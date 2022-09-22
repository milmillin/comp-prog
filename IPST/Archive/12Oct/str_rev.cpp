#include <cstdio>

using namespace std;

void recur (char *x) {
	if (*x==0) return;
	recur(x+1);
	if (*x=='_') {
		printf("%s_",x+1);
		*x=0;
		return;
	}
}

int main () {
	char x[2000];
	scanf("%s",x);
	recur(x);
	printf("%s\n",x);
	return 0;
}
