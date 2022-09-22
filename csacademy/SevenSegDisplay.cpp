#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cassert>

using namespace std;

struct bigNum {
	int n[10];
	int len () const {
		int sum=0;
		for (int i=0;i<10;i++) {
			sum+=n[i];
		}
		return sum;
	}
	bigNum add (int a) const {
		bigNum aa;
		for (int i=0;i<10;i++) {
			aa.n[i]=n[i];
			if (a==i) aa.n[i]++;
		}
		return aa;
	}
};

bool operator< (const bigNum &a, const bigNum &b) {
	if (a.n[0]==a.len()) return true;
	if (b.n[0]==b.len()) return false;

	if (a.len()!=b.len()) return a.len()<b.len();
	int aMin=10;
	int bMin=10;
	for (int i=1;i<10;i++) {
		if (a.n[i]) aMin=min(aMin,i);
		if (b.n[i]) bMin=min(bMin,i);
	}
	if (aMin!=bMin) return aMin < bMin;
	if (a.n[0]!=b.n[0]) return a.n[0]>b.n[0];
	for (int i=1;i<10;i++) {
		int aa = a.n[i];
		int bb = b.n[i];
		if (i==aMin) aa--;
		if (i==bMin) bb--;
		if (aa!=bb) return aa>bb;
	}
	return true;
}

bigNum dp[100100];
int seg[10]={6,2,5,5,4,5,6,3,7,6};

int main() {
    int k;
    scanf("%d",&k);

	if (k==1) {
		printf("-1\n");
		return 0;
	}

	dp[2] = bigNum{{0,1,0,0,0,0,0,0,0,0}};
	dp[3] = bigNum{{0,0,0,0,0,0,0,1,0,0}};
	dp[4] = bigNum{{0,0,0,0,1,0,0,0,0,0}};
	dp[5] = bigNum{{0,0,1,0,0,0,0,0,0,0}};
	dp[6] = bigNum{{1,0,0,0,0,0,0,0,0,0}};
	dp[7] = bigNum{{0,0,0,0,0,0,0,0,1,0}};	
 
    for (int i=8;i<100100;i++) {
		bool sett=false;
		for (int j=0;j<10;j++) {
			if (i-seg[j]<2) continue;
			bigNum cur = dp[i-seg[j]].add(j);
			if (cur.n[0]==cur.len()&&cur.len()>1) continue;
			if (!sett||cur<dp[i]) {
				dp[i]=cur;
				sett=true;
			}
		}
    }
	
	int fr=10;
	for (int i=1;i<10;i++) {
		if (dp[k].n[i]) fr=min(fr,i);
	}
	if (fr==10) {
		printf("0\n");
		return 0;
	}
	printf("%d",fr);
	dp[k].n[fr]--;
	for (int i=0;i<10;i++) {
		for (int j=0;j<dp[k].n[i];j++) {
			printf("%d",i);
		}
	}
	printf("\n");
}
