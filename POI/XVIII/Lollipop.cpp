#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

char x[1000100];
pair<int,int> work[2000100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	scanf("%s",x+1);
	int cur=1;
	while (x[cur]=='T'&&cur<=n) {
		cur++;
	}
	int l=cur;
	if (l!=n+1) work[1]={l,l};
	int sum=1;
	cur++;
	int r1=l;
	int s1=1;
	while (cur<=n) {
		if (x[cur]=='T') {
			sum+=2;
			work[sum]={l,cur};
			work[sum-1]={l+1,cur};
		} else {
			sum+=1;
			r1=cur;
			s1=sum;
			work[sum]={l,cur};
		}
		cur++;
	}
	for (int i=1;i<l;i++) {
		sum+=2;
		work[sum]={l-i,cur-1};	
	}
	sum=s1;

	for (int i=1;i<l;i++) {
		sum+=2;
		work[sum]={l-i,r1};
		work[sum-1]={l-i,r1-1};
	}
	int x;
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		if (work[x].first!=0) {
			printf("%d %d\n",work[x].first,work[x].second);
		} else {
			printf("NIE\n");
		}
	}
	return 0;
}
