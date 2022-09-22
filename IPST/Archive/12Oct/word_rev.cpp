#include <cstdio>
#include <cstring>

using namespace std;

char tmp[2000];

void recur(const char *x,char *y) {
	if (*x=='_') {
		printf("%s_",y+1);
		tmp[1301]=0;
		recur(x+1,tmp+1300);
	} else if (*x==0) {
		printf("%s\n",y+1);
		return;
	} else {
		*y=*x;
		recur(x+1,y-1);
	}
}

int main () {
	char x[2000];
	scanf("%s",x);
	tmp[1301]=0;
	recur(x,tmp+1300);
	return 0;
}
