#include <cstdio>
#include <cstring>

using namespace std;

char x[1000100];

int mem[1000100][6];

//0-P, 1-R, 2-S, 3-PP,4-RR,5-SS

int mic(int len,int mode) {
	if (len==1) {
		if (mode<3) return 1;
		else return 0;
	}
	if (mem[len][mode]!=-1) return mem[len][mode];
	int sum=0;

	for (int i=0;i<6;i++) {
		if (mode<3&&(i==mode||i==mode+3)) continue;
		if (mode>=3&&(i!=mode-3)) continue;
		sum+=mic(len-1,i);
	}
	sum%=2553;
	return mem[len][mode]=sum;
}

int main () {
	int n;
	scanf("%d",&n);
	scanf("%s",x);
	memset(mem,-1,sizeof(mem));
	return 0;
}
