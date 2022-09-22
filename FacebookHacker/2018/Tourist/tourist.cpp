#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

char buf[100][50];

void f() {
	int n,k;
	long long v;
	scanf("%d%d%lld",&n,&k,&v);
	for (int i=0;i<n;i++) {
		scanf("%s",buf[i]);
	}	
	int cur=((v-1)*k)%n;
	int curi=n-cur;
	for (int i=curi;i<k;i++) {
		printf("%s ",buf[(cur+i)%n]);
	}
	for (int i=0;i<min(k,curi);i++) {
		printf("%s ",buf[(cur+i)%n]);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
