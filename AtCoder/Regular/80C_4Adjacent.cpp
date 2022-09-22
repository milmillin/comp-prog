#include <cstdio>

using namespace std;

int tbl[100100];
int fact[100100];
int cnt4,cnt2;

bool f () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		if (tbl[i]%4==0) fact[i]=4,cnt4++;
		else if (tbl[i]%2==0) fact[i]=2,cnt2++;
		else fact[i]=0;
	}
	int cnt0=n-cnt4-cnt2;
	
	if (cnt4+cnt0==n&&cnt4+1==cnt0) return true;
	if (cnt4<cnt0) return false;
	if (cnt2==n) return true;
	if (cnt2&&cnt4==0) return false;
	return true;
}

int main() {
	printf("%s\n",f()?"Yes":"No");
}
