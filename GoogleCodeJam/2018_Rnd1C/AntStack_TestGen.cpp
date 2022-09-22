#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int main () {
	srand(time(NULL));
	int t=100;
	printf("%d\n",t);
	int n=10;
	for (int i=0;i<t;i++) {
		printf("%d\n",n);	
		for (int i=0;i<n;i++) {
			printf("%d ",rand()%1000+1);
		}
		printf("\n");
	}
	return 0;
}
