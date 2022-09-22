#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int pos[100100];
double want[100100];

int main () {
	int m,n;
	scanf("%d%d",&m,&n);
	double interval = 2.0*m/n;
	char x;
	for (int i=0;i<n;i++) {
		scanf("%d %c",&pos[i],&x);
	}	
	sort(pos,pos+n);
	for (int i=1;i<n;i+=2) {
		pos[i]=2*m-pos[i];
	}
	sort(pos,pos+n);
	for (int i=0;i<n;i++) {
		want[i]=interval*i;	
	}
	sort(want,want+n);
	double mx=0;
	double mn=1e9;
	for (int i=0;i<n;i++) {
		mx=max(mx,pos[i]-want[i]);
		mn=min(mn,pos[i]-want[i]);
	}
	printf("%f\n",(mx-mn)/2);
	return 0;
}
