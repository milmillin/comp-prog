#include <cstdio>

using namespace std;

int main () {
	int k,r;
	scanf("%d%d",&k,&r);
	long long kk=k;
	int cnt=1;
	while (true) {
		if (kk%10==r||kk%10==0) break;
		kk+=k;
		cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}
