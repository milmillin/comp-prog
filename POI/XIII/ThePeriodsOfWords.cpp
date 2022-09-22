#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

char x[1000100];
int pre[1000100];
int a[1000100];
int main () {
	int n;
	scanf("%d",&n);
	scanf("%s",x+1);
	
	//pre[0]=0;
	//int i=1;
	int cur=0;

	//for (int i=1;i<n;i++) {
		//while (k>=0&&x[i]!=x[k+1]) k=pre[k];
		//if (x[i]==x[k+1]) {
			//k++;
		//}
		//pre[i]=k;
		//printf("%d\n",k);
	//}

	//while (i<n) {
		//if (x[i]==x[cur]) {
			//cur++;
			//pre[i]=cur;
			//i++;	
		//} else {
			//if (cur!=0) {
				//cur=pre[cur-1];
			//} else {
				//pre[i]=0;
				//i++;
			//}
		//}
	//}
	memset(a,-1,sizeof(a));
	long long sum=0;		
	for (int i=2;i<=n;i++) {
		//if (x[cur+1]==x[i]) cur++;
		//else if (x[1]==x[i]) cur=1;
		//else cur=0;
		while(cur!=0&&x[cur+1]!=x[i])cur=pre[cur];
		if(x[cur+1]==x[i])cur++;
		pre[i]=cur;
		//printf("--%d %d %d\n",cur,i,pre[cur]);
		int curr=cur;
		while (pre[curr]!=0) {

			curr=pre[curr];
			if (a[curr]!=-1) {
				curr=a[curr];
				break;
			}
		}
		a[cur]=curr;
		
		if (cur>0) sum+=i-curr;
		//printf("%d %d\n",i,cur);
	}	
	printf("%lld\n",sum);
	return 0;
}
