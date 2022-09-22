#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int cnt[1000];
int cnt3[1000];

int main () {
	int q;
	scanf("%d",&q);
	int mx2=0;
	int mx3=0;
	while (q--) {
		string x;
		cin >> x;
		int n = x.size();

		int val;
		for (int i=0;i<n-1;i++) {
			val = (x[i]-'0')*10+(x[i+1]-'0');
			cnt[val]++;
			mx2=max(mx2,cnt[val]);
			if (i!=n-2) {
				val = (x[i]-'0')*100+(x[i+1]-'0')*10+(x[i+2]-'0');
				//printf("--%d\n",val);
				cnt3[val]++;
				mx3=max(mx3,cnt3[val]);
			}	
		}
	}
	for (int i=0;i<=99;i++) {
		if (cnt[i]==mx2) {
			if (i>=10) printf("%d ",i);
			else printf("0%d ",i);
		}
	}
	printf("\n");
	for (int i=0;i<=999;i++) {
		if (cnt3[i]==mx3) {
			if (i>=100) printf("%d ",i);
			else if (i>=10) printf("0%d ",i);
			else if (i>=1) printf("00%d ",i);
			else printf("000 ");
		}
	}
	printf("\n");
	
	return 0;
}
