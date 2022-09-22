#include <algorithm>
#include <cstdio>

using namespace std;

int tbl[20100];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",tbl+i);
		tbl[i+n]=tbl[i];
	}
	int ans=0;
	bool fst=false;
	int fstSum=0;
	int stk=0;
	for (int i=1;i<n;i++) {
		stk=0;
		fst=true;
		for (int j=0;j<n;j++) {
			if (tbl[j]==tbl[j+i]) {
				stk++;
			} else {
				if (fst) {
					fstSum=stk;
					fst=false;
				}
				stk=0;
			}
			ans=max(ans,stk);
		}
		ans=max(ans,stk+fstSum);
	}
	printf("%d\n",(ans==n)?-1:ans);
	return 0;
}
