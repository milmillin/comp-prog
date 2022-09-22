#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int mem[2000];

bool contain(int a,int b) {
	while (a) {
		if (a%10==b) return true;
		a/=10;
	}
	return false;
}

int recur(int x) {
	if (x==1) return 0;
	if (x<1) return 2e9;
	if (mem[x]!=-1) return mem[x];
	int now=2e9;
	for (int i=2;i<=5;i++) {
		if (contain(x,i)) continue;
		if (x%i==0) continue;
		now=min(now,recur(x-i)+1);
	}
	return mem[x]=now;
}

int main () {
	memset(mem,-1,sizeof(mem));
	int x;
	scanf("%d",&x);
	printf("%d\n",(recur(x)>=2e9)?-1:recur(x));
	return 0;
}
