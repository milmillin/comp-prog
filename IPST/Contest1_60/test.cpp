#include <cstdio>

using namespace std;

int main () {
	int sum=0;
	for (int i=2;i<1000100;i++) {
		for (int j=i;j<1000100;j+=i) {
			sum++;
		}
	}
	printf("%d\n",sum);
	return 0;
}
