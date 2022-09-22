#include <cstdio>
#include <algorithm>

using namespace std;

int main () {
	int n,s;
	scanf("%d%d",&n,&s);
	//vector<int> tbl(n);
	int a,b;
	scanf("%d%d",&a,&b);
	printf("0\n");
	double timee = (double)s/b+a;
	for (int i=1;i<n;i++) {
		//scanf("%d",&tbl[i]);
		scanf("%d%d",&a,&b);
		double newT = (double)s/b+a;
		if (newT<timee)	printf("%d\n",(int)ceil(b-s/(timee-a)));
		else {
			printf("0\n");
			timee=newT;
		}
	}
	//printf("yay\n");
	return 0;
}
