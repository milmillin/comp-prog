#include <cstdio>

using namespace std;

bool a[10];
bool b[10];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		a[x]=true;
	}
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		b[x]=true;
	}
	for (int i=1;i<10;i++) {
		if (a[i]==true&&b[i]==true) {
			printf("%d\n",i);
			return 0;
		}
	}
	for (int i=1;i<10;i++) {
		for (int j=1;j<10;j++) {
			if ((a[i]==true&&b[j]==true)||(b[i]==true&&a[j]==true)){
				printf("%d%d\n",i,j);
				return 0;
			}
		}	
	}
	return 0;
}
