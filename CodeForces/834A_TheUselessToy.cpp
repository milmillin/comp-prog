#include <cstdio>

using namespace std;

int mp[256];

int main () {
	char st,end;
	scanf(" %c %c",&st,&end);
	int n;
	scanf("%d",&n);
	mp['v']=0;
	mp['<']=1;
	mp['^']=2;
	mp['>']=3;
	int a=mp[st];
	int b=mp[end];
	bool cw=false;
	bool ccw=false;
	if ((a+n)%4==b) cw=true;
	if (((a-n)%4+4)%4==b) ccw=true;
	if (ccw&&cw) {
		printf("undefined\n");
		return 0;
	} else {
		printf("%s\n",(cw)?"cw":"ccw");
	}
	return 0;
}
